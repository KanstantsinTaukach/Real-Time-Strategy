// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "RTSSelectableInterface.h"
#include "RTSNavigableInterface.h"
#include "RTSHUD.h"
#include "RTSBasePawn.h"

ARTSPlayerController::ARTSPlayerController()
{
    bShowMouseCursor = true;
}

void ARTSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    GameHUD = Cast<ARTSHUD>(GetHUD());
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
        EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &ARTSPlayerController::SelectStart);
        EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ARTSPlayerController::SelectOnGoing);
        EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ARTSPlayerController::SelectEnd);
        EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &ARTSPlayerController::CommandSelectedActors);
    }
}

void ARTSPlayerController::Select(const FInputActionValue& Value)
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

    if (SelectedActor && SelectedActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
    {
        IRTSSelectableInterface::Execute_SelectActor(SelectedActor, false);
    }

    SelectedActor = HitResult.GetActor();

    if (SelectedActor && SelectedActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
    {
        IRTSSelectableInterface::Execute_SelectActor(SelectedActor, true);
    }
}

void ARTSPlayerController::SelectStart(const FInputActionValue& Value)
{
    float MouseX, MouseY;
    GetMousePosition(MouseX, MouseY);
    SelectionStartPosition = FVector2d(MouseX, MouseY);
}

void ARTSPlayerController::SelectOnGoing(const FInputActionValue& Value)
{
    float MouseX, MouseY;
    GetMousePosition(MouseX, MouseY);
    SelectionSize = FVector2d(MouseX - SelectionStartPosition.X, MouseY - SelectionStartPosition.Y);

    if (GameHUD)
    {
        GameHUD->ShowSelectionRect(SelectionStartPosition, SelectionSize);
    }
}

void ARTSPlayerController::SelectEnd(const FInputActionValue& Value)
{
    if (GameHUD)
    {
        GameHUD->HideSelectionRect();

        FTimerHandle SelectMultipleActorsTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(
            SelectMultipleActorsTimerHandle, this, &ARTSPlayerController::SelectMultipleActors, 0.05f, false);
    }
}

void ARTSPlayerController::SelectMultipleActors()
{
    if (GameHUD)
    {
        for (auto* SomeActor : SelectedActors)
        {
            if (SomeActor && SomeActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
            {
                IRTSSelectableInterface::Execute_SelectActor(SomeActor, false);
            }
        }
        SelectedActors.Empty();

        TArray<ARTSBasePawn*> AllSelectedActors = GameHUD->GetSelectedActors();
        for (auto* SomeActor : AllSelectedActors)
        {
            if (SomeActor && SomeActor->GetClass()->ImplementsInterface(URTSFactionInterface::StaticClass()))
            {
                int32 ActorFaction = IRTSFactionInterface::Execute_GetFaction(SomeActor);
                if (FactionID != ActorFaction)
                {
                    continue;
                }
            }

            if (SomeActor && SomeActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
            {
                IRTSSelectableInterface::Execute_SelectActor(SomeActor, true);
                SelectedActors.AddUnique(SomeActor);
            }
        }

        OnActorsSelected.Broadcast(SelectedActors);
    }
}

void ARTSPlayerController::CommandSelectedActors(const FInputActionValue& Value)
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

    if (!HitResult.bBlockingHit) return;

    if (SelectedActors.Num() > 0)
    {
        int8 i = SelectedActors.Num() / -2;
        for (auto* SomeActor : SelectedActors)
        {
            if (SomeActor && SomeActor->GetClass()->ImplementsInterface(URTSNavigableInterface::StaticClass()))
            {
                IRTSNavigableInterface::Execute_MoveToLocation(SomeActor, HitResult.Location + FVector(0.0, 100.0 * i, 0.0));
                ++i;
            }
        }
    }
    else
    {
        if (SelectedActor && SelectedActor->GetClass()->ImplementsInterface(URTSNavigableInterface::StaticClass()))
        {
            if (SelectedActor->GetClass()->ImplementsInterface(URTSFactionInterface::StaticClass()))
            {
                if (FactionID == IRTSFactionInterface::Execute_GetFaction(SelectedActor))
                {
                    IRTSNavigableInterface::Execute_MoveToLocation(SelectedActor, HitResult.Location);
                }
            }
        }
    }
}