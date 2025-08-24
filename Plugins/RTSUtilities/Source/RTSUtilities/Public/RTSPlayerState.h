// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RTSPlayerState.generated.h"

class URTSResourceAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class RTSUTILITIES_API ARTSPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ARTSPlayerState();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
    TObjectPtr<URTSResourceAttributeSet> ResourceAttributeSet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
