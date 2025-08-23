// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RTSLib.h"
#include "RTSActorData.generated.h"

USTRUCT(BlueprintType)
struct FActorData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorData")
    EActorType ActorType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorData")
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorData")
    TObjectPtr<UTexture2D> Texture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorData")
    TObjectPtr<UMaterialInterface> IconMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorData")
    int32 CurrentHealth;

    FActorData() : ActorType(EActorType::Villager), DisplayName(TEXT("")), Texture(nullptr), CurrentHealth(0) {}

    FActorData(EActorType Type, FString Name, UTexture2D* InTexture, int32 HealthValue)
        : ActorType(Type), DisplayName(Name), Texture(InTexture), CurrentHealth(HealthValue) {}
};