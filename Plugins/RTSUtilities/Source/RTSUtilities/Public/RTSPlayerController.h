// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSFactionInterface.h"
#include "RTSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ARTSHUD;

struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorsSelectedSignature, const TArray<AActor*>&, InSelectedActors);

UCLASS()
class RTSUTILITIES_API ARTSPlayerController : public APlayerController, public IRTSFactionInterface
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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Faction")
    int32 FactionID = 0;

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

    void Select(const FInputActionValue& Value);

    void SelectStart(const FInputActionValue& Value);
    void SelectOnGoing(const FInputActionValue& Value);
    void SelectEnd(const FInputActionValue& Value);

    void SelectMultipleActors();

    void CommandSelectedActors(const FInputActionValue& Value);

    int32 GetFaction_Implementation() override { return FactionID; };
    void SetFaction_Implementation(int32 NewFaction) override { FactionID = NewFaction; };

private:
    UPROPERTY(BlueprintAssignable, Category = "Delegates")
    FOnActorsSelectedSignature OnActorsSelected;

    UPROPERTY()
    TObjectPtr<AActor> SelectedActor;

    UPROPERTY()
    TArray<AActor*> SelectedActors;

    UPROPERTY()
    TObjectPtr<ARTSHUD> GameHUD;

    FVector2D SelectionStartPosition;
    FVector2D SelectionSize;
};
