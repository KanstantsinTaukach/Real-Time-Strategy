// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSBaseBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RTSFactionData.h"

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