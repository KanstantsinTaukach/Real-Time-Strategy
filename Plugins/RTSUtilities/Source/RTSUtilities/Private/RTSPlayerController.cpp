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
        for (AActor* SomeActor : SelectedActors)
        {
            if (SomeActor)
            {
                if (SomeActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
                {
                    IRTSSelectableInterface::Execute_SelectActor(SomeActor, false);
                }
            }
        }

        SelectedActors = GameHUD->GetSelectedActors();

        for (AActor* SomeActor : SelectedActors)
        {
            if (SomeActor)
            {
                if (SomeActor->GetClass()->ImplementsInterface(URTSSelectableInterface::StaticClass()))
                {
                    IRTSSelectableInterface::Execute_SelectActor(SomeActor, true);
                }
            }
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