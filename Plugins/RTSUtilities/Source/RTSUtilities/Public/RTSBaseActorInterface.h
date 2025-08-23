// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RTSLib.h"
#include "RTSBaseActorInterface.generated.h"

class ARTSBaseBuilding;

UINTERFACE(MinimalAPI)
class URTSBaseActorInterface : public UInterface
{
    GENERATED_BODY()
};

class RTSUTILITIES_API IRTSBaseActorInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BaseActorInterface") 
    EActorType GetActorType();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BaseActorInterface")
    TArray<TSubclassOf<ARTSBaseBuilding>> GetBuildingOptions();
};
