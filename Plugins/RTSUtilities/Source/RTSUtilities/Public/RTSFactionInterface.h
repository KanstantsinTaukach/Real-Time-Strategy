// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSFactionInterface.generated.h"

UINTERFACE(MinimalAPI)
class URTSFactionInterface : public UInterface
{
    GENERATED_BODY()
};

class RTSUTILITIES_API IRTSFactionInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Faction")
    int32 GetFaction();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Faction") 
    void SetFaction(int32 NewFaction);
};
