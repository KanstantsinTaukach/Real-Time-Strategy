// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RTSSelectableInterface.h"
#include "RTSBaseBuilding.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class RTSUTILITIES_API ARTSBaseBuilding : public AActor, public IRTSSelectableInterface
{
    GENERATED_BODY()

public:
    ARTSBaseBuilding();

    void SelectActor_Implementation(bool IsSelected) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BuildingStaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> SelectedIndicatorComponent;
};
