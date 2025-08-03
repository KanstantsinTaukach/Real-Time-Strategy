// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSSelectableInterface.generated.h"

UINTERFACE(MinimalAPI)
class URTSSelectableInterface : public UInterface
{
    GENERATED_BODY()
};

class RTSUTILITIES_API IRTSSelectableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SelectableInterface")
    void SelectActor(const bool IsSelected);
};
