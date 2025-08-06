// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "RTSSelectableInterface.h"
#include "RTSNavigableInterface.h"

ARTSPlayerController::ARTSPlayerController()
{
    bShowMouseCursor = true;
}

void ARTSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!DefaultInputMappingContext) return;

    auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(DefaultInputMappingContext, 0);
    }

    if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ARTSPlayerController::Select);
        EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &ARTSPlayerController::CommandSelectedActor);
    }
}

void ARTSPlayerController::Select(const FInputActionValue& Value)
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

    if (SelectedActor)
    {
        if (SelectedActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
        {
            IRTSSelectableInterface::Execute_SelectActor(SelectedActor, false);
        }
    }

    SelectedActor = HitResult.GetActor();

    if (SelectedActor)
    {
        if (SelectedActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
        {
            IRTSSelectableInterface::Execute_SelectActor(SelectedActor, true);
        }
    }
}

    void ARTSPlayerController::CommandSelectedActor(const FInputActionValue& Value)
    {
        if (SelectedActor)
        {
            if (SelectedActor->GetClass()->ImplementsInterface(URTSNavigableInterface::StaticClass()))
            {
                FHitResult HitResult;
                GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

                if (HitResult.bBlockingHit)
                {
                    IRTSNavigableInterface::Execute_MoveToLocation(SelectedActor, HitResult.Location);
                }
            }
        }
    }