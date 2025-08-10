// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RTSLib.h"
#include "RTSResourceData.generated.h"

USTRUCT(BlueprintType)
struct FResourceData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    EResourceTypes ResourceType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    UTexture2D* Texture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
    int32 DefaultValue;

    FResourceData() : ResourceType(EResourceTypes::Wood), DisplayName(TEXT("")), Texture(nullptr), DefaultValue(0) {}

    FResourceData(EResourceTypes Type, FString Name, UTexture2D* InTexture, int32 Value)
        : ResourceType(Type), DisplayName(Name), Texture(InTexture), DefaultValue(Value) {}
};
