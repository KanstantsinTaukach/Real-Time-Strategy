// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ARTSHUD;

struct FInputActionValue;

UCLASS()
class RTSUTILITIES_API ARTSPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ARTSPlayerController();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> SelectAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> CommandAction;

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

    void Select(const FInputActionValue& Value);

    void SelectStart(const FInputActionValue& Value);
    void SelectOnGoing(const FInputActionValue& Value);
    void SelectEnd(const FInputActionValue& Value);

    void SelectMultipleActors();

    void CommandSelectedActors(const FInputActionValue& Value);

private:
    UPROPERTY()
    TObjectPtr<AActor> SelectedActor;

    UPROPERTY()
    TArray<AActor*> SelectedActors;

    UPROPERTY()
    TObjectPtr<ARTSHUD> GameHUD;

    FVector2D SelectionStartPosition;
    FVector2D SelectionSize;
};
