// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSControllerPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"

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

    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
}

void ARTSControllerPawn::BeginPlay()
{
    Super::BeginPlay();
}

void ARTSControllerPawn::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    EdgeScrollWithMouse();
}

void ARTSControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARTSControllerPawn::Move);
        EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARTSControllerPawn::Zoom);
    }
}

void ARTSControllerPawn::Move(const FInputActionValue& Value) 
{
    const FVector2D MovementInput = Value.Get<FVector2D>();

    if (Controller)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0, Rotation.Yaw, 0.0);

        const FVector ForwartDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwartDirection, MovementInput.Y);
        AddMovementInput(RightDirection, MovementInput.X);
    }
}

void ARTSControllerPawn::Zoom(const FInputActionValue& Value) 
{
    const float ZoomDirection = Value.Get<float>();

    if (Controller)
    {
        float DesiredOrthoWidth = CameraComponent->OrthoWidth + ZoomDirection * CameraZoomSpeed;
        DesiredOrthoWidth = FMath::Clamp(DesiredOrthoWidth, MinCameraOrthoWidth, MaxCameraOrthoWidth);
        CameraComponent->OrthoWidth = DesiredOrthoWidth;
    }
}

void ARTSControllerPawn::EdgeScrollWithMouse()
{
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    if (!PlayerController) return;

    float MouseX = 0.0f, MouseY = 0.0f;
    if (PlayerController->GetMousePosition(MouseX, MouseY))
    {
        FVector2d VeiwportSize;
        if (GEngine && GEngine->GameViewport)
        {
            GEngine->GameViewport->GetViewportSize(VeiwportSize);

            float EdgeThresholdX = VeiwportSize.X / 100 * 5;
            float EdgeThresholdY = VeiwportSize.Y / 100 * 5;
            FVector2D MovementInput = FVector2D::ZeroVector;

            if (MouseX < EdgeThresholdX)
            {
                MovementInput.X = -1.0f;
            }
            if (MouseX > (VeiwportSize.X - EdgeThresholdX))
            {
                MovementInput.X = 1.0f;
            }
            if (MouseY < EdgeThresholdY)
            {
                MovementInput.Y = 1.0f;
            }
            if (MouseY > (VeiwportSize.Y - EdgeThresholdY))
            {
                MovementInput.Y = -1.0f;
            }

            if (!MovementInput.IsNearlyZero())
            {
                Move(FInputActionValue(MovementInput));
            }
        }
    }
}