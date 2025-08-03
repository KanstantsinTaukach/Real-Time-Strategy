// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSBasePawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;

UCLASS()
class RTSUTILITIES_API ARTSBasePawn : public APawn
{
    GENERATED_BODY()

public:
    ARTSBasePawn();

    UFUNCTION()
    void SelectActor(bool IsSelected);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UCapsuleComponent> CapsuleComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> SelectedIndicatorComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
};
