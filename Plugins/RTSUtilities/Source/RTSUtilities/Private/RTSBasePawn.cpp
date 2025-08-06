// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ARTSBasePawn::ARTSBasePawn()
{
    PrimaryActorTick.bCanEverTick = false;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
    RootComponent = CapsuleComponent;
    CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
    SkeletalMeshComponent->SetupAttachment(RootComponent);

    SelectedIndicatorComponent = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicatorComponent");
    SelectedIndicatorComponent->SetupAttachment(RootComponent);
    SelectedIndicatorComponent->SetHiddenInGame(true);
    SelectedIndicatorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
}

void ARTSBasePawn::BeginPlay()
{
    Super::BeginPlay();
}

void ARTSBasePawn::SelectActor_Implementation(const bool IsSelected) 
{
    SelectedIndicatorComponent->SetHiddenInGame(!IsSelected);
}

void ARTSBasePawn::MoveToLocation_Implementation(const FVector TargetLocation) 
{
    FVector MoveTargetLocation = TargetLocation;
    MoveTargetLocation.Z = 0 + CapsuleComponent->GetComponentLocation().Z;
    SetActorLocation(MoveTargetLocation);
}