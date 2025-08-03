// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ARTSBasePawn;

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

    virtual void SetupInputComponent() override;

    void Select(const FInputActionValue& Value);

private:
    UPROPERTY()
    TObjectPtr<ARTSBasePawn> SelectedPawn;
};
