// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSBaseBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RTSFactionData.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

ARTSBaseBuilding::ARTSBaseBuilding()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
    RootComponent = CollisionComponent;
    CollisionComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

    BuildingStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingStaticMesh");
    BuildingStaticMesh->SetupAttachment(CollisionComponent);
    BuildingStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SelectedIndicatorComponent = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicatorComponent");
    SelectedIndicatorComponent->SetupAttachment(CollisionComponent);
    SelectedIndicatorComponent->SetHiddenInGame(true);
    SelectedIndicatorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARTSBaseBuilding::BeginPlay()
{
    Super::BeginPlay();

    check(FactionTable);

    PlacementZOffset = CollisionComponent->GetScaledBoxExtent().Z;
}

void ARTSBaseBuilding::SelectActor_Implementation(bool IsSelected)
{
    SelectedIndicatorComponent->SetHiddenInGame(!IsSelected);
}

void ARTSBaseBuilding::SetFaction_Implementation(int32 NewFaction)
{
    if (NewFaction < 0) return;

    FactionID = NewFaction;

    const auto RowName = FactionTable->GetRowNames()[NewFaction];
    auto* FactionData = FactionTable->FindRow<FFactionData>(RowName, {});

    if (FactionData)
    {
        FVector ColorVector = FVector(FactionData->FactionColor.R, FactionData->FactionColor.G, FactionData->FactionColor.B);
        BuildingStaticMesh->SetVectorParameterValueOnMaterials("FactionColor", ColorVector);
        SelectedIndicatorComponent->SetVectorParameterValueOnMaterials("FactionColor", ColorVector);
    }
}

void ARTSBaseBuilding::EnablePlacingMode()
{
    if (!GetWorld()) return;

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        EnableInput(PC);

        UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent);
        if (EnhancedInputComponent)
        {
            EnhancedInputComponent->BindAction(PlaceAction, ETriggerEvent::Completed, this, &ARTSBaseBuilding::PlaceBuilding);
        }
    }

    GetWorld()->GetTimerManager().SetTimer(PlacementValidationTimer, this, &ARTSBaseBuilding::CheckPlacementValidity, 0.03f, true);

    this->SetActorEnableCollision(false);
}

void ARTSBaseBuilding::CheckPlacementValidity()
{
    ToggleBuildingValidity(bCanPlaceBuilding);
    bCanPlaceBuilding = false;

    if (!GetWorld()) return;

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    FHitResult HitResult;
    PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
    if (!HitResult.bBlockingHit) return;

    FVector TargetLocation = HitResult.Location;
    TargetLocation.Z += PlacementZOffset;
    SetActorLocation(TargetLocation);

    if (!HasPlacementTag(HitResult, RequiredTag)) return;

    FVector TraceStart = HitResult.Location + FVector(0.0, 0.0, PlacementZOffset);
    FVector TraceEnd = TraceStart + FVector::UpVector;

    FCollisionShape CollisionShape = FCollisionShape::MakeBox(BuildingExtents / 2);
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    CollisionParams.bTraceComplex = false;

    TArray<FHitResult> OutHits;
    bool bAnyHit = GetWorld()->SweepMultiByChannel(
        OutHits, TraceStart, TraceEnd, GetActorRotation().Quaternion(), ECC_Visibility, CollisionShape, CollisionParams);
    if (bAnyHit) return;

    bCanPlaceBuilding = true;
}

bool ARTSBaseBuilding::HasPlacementTag(const FHitResult& HitResult, FName Tag) const
{
    if (!Tag.IsValid() || Tag == NAME_None) return false;

    AActor* HitActor = HitResult.GetActor();
    if (HitActor && HitActor->ActorHasTag(Tag)) return true;

    UPrimitiveComponent* HitComp = HitResult.GetComponent();
    if (HitComp && HitComp->ComponentTags.Contains(Tag)) return true;

    return false;
}

void ARTSBaseBuilding::ToggleBuildingValidity(bool bValid)
{
    BuildingStaticMesh->SetScalarParameterValueOnMaterials("Invalid", bValid);
}

void ARTSBaseBuilding::PlaceBuilding(const FInputActionValue& Value)
{
    if (!GetWorld()) return;

    if (!bCanPlaceBuilding)
    {
        Destroy();
        return;
    }

    GetWorld()->GetTimerManager().ClearTimer(PlacementValidationTimer);

    this->SetActorEnableCollision(true);
}

void ARTSBaseBuilding::CancelBuildingPlacement(const FInputActionValue& Value) {}