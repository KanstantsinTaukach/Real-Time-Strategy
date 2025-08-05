// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSBaseBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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

    if (BuildingStaticMesh->GetStaticMesh())
    {
        FBoxSphereBounds MeshBounds = BuildingStaticMesh->GetStaticMesh()->GetBounds();

        CollisionComponent->SetBoxExtent(MeshBounds.BoxExtent);

        BuildingStaticMesh->SetRelativeLocation(FVector::ZeroVector);
    }
}

void ARTSBaseBuilding::SelectActor_Implementation(bool IsSelected)
{
    SelectedIndicatorComponent->SetHiddenInGame(!IsSelected);
}