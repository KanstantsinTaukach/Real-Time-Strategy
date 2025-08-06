// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSNavigableInterface.generated.h"

UINTERFACE(MinimalAPI)
class URTSNavigableInterface : public UInterface
{
    GENERATED_BODY()
};

class RTSUTILITIES_API IRTSNavigableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "NavigableInterface")
    void MoveToLocation(const FVector TargetLocation);
};
