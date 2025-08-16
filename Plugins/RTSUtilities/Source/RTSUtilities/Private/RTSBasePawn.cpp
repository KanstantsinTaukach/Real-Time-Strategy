// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"
#include "RTSFactionData.h"

ARTSBasePawn::ARTSBasePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
    RootComponent = CapsuleComponent;
    CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
    CapsuleComponent->SetCanEverAffectNavigation(false);

    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
    SkeletalMeshComponent->SetupAttachment(RootComponent);

    SelectedIndicatorComponent = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicatorComponent");
    SelectedIndicatorComponent->SetupAttachment(RootComponent);
    SelectedIndicatorComponent->SetHiddenInGame(true);
    SelectedIndicatorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
    FloatingPawnMovement->MaxSpeed = 300.0f;
}

void ARTSBasePawn::BeginPlay()
{
    Super::BeginPlay();

    check(FactionTable);
}

void ARTSBasePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    OrientPawnToMovementDirection();
}

void ARTSBasePawn::OrientPawnToMovementDirection()
{
    if (!bMoving) return;

    FVector MoveDirection = (MoveTargetLocation - GetActorLocation());
    if (MoveDirection.Length() < AcceptanceDistance)
    {
        bMoving = false;
        return;
    }

    MoveDirection.Normalize(1);

    FRotator DesiredRotation = UKismetMathLibrary::MakeRotFromX(MoveDirection);
    DesiredRotation.Pitch = 0;
    DesiredRotation.Roll = 0;

    FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), DesiredRotation, GetWorld()->GetDeltaSeconds(), CharacterTurnSpeed);
    SetActorRotation(NewRotation);
}

void ARTSBasePawn::SelectActor_Implementation(const bool IsSelected)
{
    SelectedIndicatorComponent->SetHiddenInGame(!IsSelected);
}

void ARTSBasePawn::MoveToLocation_Implementation(const FVector TargetLocation)
{
    MoveTargetLocation = TargetLocation;
    MoveTargetLocation.Z = 0 + CapsuleComponent->GetComponentLocation().Z;

    bMoving = true;

    AAIController* PawnAIController = Cast<AAIController>(GetController());
    if (PawnAIController)
    {
        PawnAIController->MoveToLocation(MoveTargetLocation, AcceptanceDistance);
    }
}

void ARTSBasePawn::SetFaction_Implementation(int32 NewFaction)
{
    if (NewFaction < 0) return;

    FactionID = NewFaction;

    const auto RowName = FactionTable->GetRowNames()[NewFaction];
    auto* FactionData = FactionTable->FindRow<FFactionData>(RowName, {});

    if (FactionData)
    {
        FVector ColorVector = FVector(FactionData->FactionColor.R, FactionData->FactionColor.G, FactionData->FactionColor.B);
        SkeletalMeshComponent->SetVectorParameterValueOnMaterials("FactionColor", ColorVector);
        SelectedIndicatorComponent->SetVectorParameterValueOnMaterials("FactionColor", ColorVector);
    }
}