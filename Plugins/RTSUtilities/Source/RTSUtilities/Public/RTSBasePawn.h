// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSSelectableInterface.h"
#include "RTSNavigableInterface.h"
#include "RTSBasePawnInterface.h"
#include "RTSLib.h"
#include "RTSBasePawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;

UCLASS()
class RTSUTILITIES_API ARTSBasePawn : public APawn, public IRTSSelectableInterface, public IRTSNavigableInterface, public IRTSBasePawnInterface
{
    GENERATED_BODY()

public:
    ARTSBasePawn();

    virtual void Tick(float DeltaTime) override;

    void SelectActor_Implementation(const bool IsSelected) override;

    void MoveToLocation_Implementation(const FVector TargetLocation) override;

    EPawnType GetPawnType_Implementation() override { return PawnType; } 

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UCapsuleComponent> CapsuleComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> SelectedIndicatorComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PawnType")
    EPawnType PawnType = EPawnType::Villager;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float AcceptanceDistance = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float CharacterTurnSpeed = 5.0f;

private:
    FVector MoveTargetLocation;
    bool bMoving = false;

    void OrientPawnToMovementDirection();
};
