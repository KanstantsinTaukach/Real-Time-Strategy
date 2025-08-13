// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RTSFactionData.generated.h"

USTRUCT(BlueprintType)
struct FFactionData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
    FString FactionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
    FLinearColor FactionColor;

    FFactionData() : FactionName(TEXT("Green")), FactionColor(FLinearColor::Green) {}
};