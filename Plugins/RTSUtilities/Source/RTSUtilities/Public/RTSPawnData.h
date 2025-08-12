// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RTSLib.h"
#include "RTSPawnData.generated.h"

USTRUCT(BlueprintType)
struct FPawnData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
    EPawnType PawnType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
    TSoftObjectPtr<UTexture2D> Texture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
    int32 CurrentHealth;

    FPawnData() : PawnType(EPawnType::Villager), DisplayName(TEXT("")), Texture(nullptr), CurrentHealth(0) {}

    FPawnData(EPawnType Type, FString Name, UTexture2D* InTexture, int32 HealthValue)
        : PawnType(Type), DisplayName(Name), Texture(InTexture), CurrentHealth(HealthValue) {}
};