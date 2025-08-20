// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSSelectableInterface.h"
#include "RTSFactionInterface.h"
#include "RTSBaseBuilding.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UInputAction;

struct FInputActionValue;

UCLASS()
class RTSUTILITIES_API ARTSBaseBuilding : public AActor, public IRTSSelectableInterface, public IRTSFactionInterface
{
    GENERATED_BODY()

public:
    ARTSBaseBuilding();

    void SelectActor_Implementation(bool IsSelected) override;

    int32 GetFaction_Implementation() override { return FactionID; };
    void SetFaction_Implementation(int32 NewFaction) override;

    UFUNCTION(BlueprintCallable, Category = "Building")
    void EnablePlacingMode();

    void CheckPlacementValidity();

    void PlaceBuilding(const FInputActionValue& Value);

    void CancelBuildingPlacement(const FInputActionValue& Value);

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
    TObjectPtr<UInputAction> PlaceAction;

private:
    UPROPERTY()
    FTimerHandle PlacementValidationTimer;
};
