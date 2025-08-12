// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSLib.h"
#include "RTSBasePawnInterface.generated.h"

UINTERFACE(MinimalAPI)
class URTSBasePawnInterface : public UInterface
{
    GENERATED_BODY()
};

class RTSUTILITIES_API IRTSBasePawnInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BasePawnInterface") 
    EPawnType GetPawnType();
};
