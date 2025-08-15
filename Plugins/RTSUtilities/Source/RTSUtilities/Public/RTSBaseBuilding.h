// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSSelectableInterface.h"
#include "RTSFactionInterface.h"
#include "RTSBaseBuilding.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class RTSUTILITIES_API ARTSBaseBuilding : public AActor, public IRTSSelectableInterface, public IRTSFactionInterface
{
    GENERATED_BODY()

public:
    ARTSBaseBuilding();

    void SelectActor_Implementation(bool IsSelected) override;

    int32 GetFaction_Implementation() override { return FactionID; };
    void SetFaction_Implementation(int32 NewFaction) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BuildingStaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> SelectedIndicatorComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
    int32 FactionID = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    TObjectPtr<UDataTable> FactionTable;
};
