// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

ARTSBasePawn::ARTSBasePawn()
{
    PrimaryActorTick.bCanEverTick = true;

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

void ARTSBasePawn::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    Move();
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
}

void ARTSBasePawn::Move()
{
    if (!bMoving) return;

    FVector MoveDirection = (MoveTargetLocation - GetActorLocation());
    if (MoveDirection.Length() < AcceptanceDistance)
    {
        bMoving = false;
        return;
    }

    MoveDirection.Normalize(1);
    AddMovementInput(MoveDirection, 1.0f);

    FRotator DesiredRotation = UKismetMathLibrary::MakeRotFromX(MoveDirection);
    DesiredRotation.Pitch = 0;
    DesiredRotation.Roll = 0;

    FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), DesiredRotation, GetWorld()->GetDeltaSeconds(), CharacterTurnSpeed);
    SetActorRotation(NewRotation);
}