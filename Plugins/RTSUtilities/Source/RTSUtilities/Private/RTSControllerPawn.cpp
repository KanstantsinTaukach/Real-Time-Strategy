// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSControllerPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARTSControllerPawn::ARTSControllerPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
    RootComponent = CapsuleComponent;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
    CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
}

void ARTSControllerPawn::BeginPlay()
{
    Super::BeginPlay();
}

void ARTSControllerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARTSControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
