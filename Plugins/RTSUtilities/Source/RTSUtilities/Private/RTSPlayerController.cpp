// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "RTSSelectableInterface.h"

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