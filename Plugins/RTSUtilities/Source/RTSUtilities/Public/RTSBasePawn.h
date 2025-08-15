// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSSelectableInterface.h"
#include "RTSNavigableInterface.h"
#include "RTSBasePawnInterface.h"
#include "RTSFactionInterface.h"
#include "RTSLib.h"
#include "RTSBasePawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;

UCLASS()
class RTSUTILITIES_API ARTSBasePawn : public APawn, public IRTSSelectableInterface, public IRTSNavigableInterface, public IRTSBasePawnInterface, public IRTSFactionInterface
{
    GENERATED_BODY()

public:
    ARTSBasePawn();

    virtual void Tick(float DeltaTime) override;

    void SelectActor_Implementation(const bool IsSelected) override;

    void MoveToLocation_Implementation(const FVector TargetLocation) override;

    EPawnType GetPawnType_Implementation() override { return PawnType; } 

    int32 GetFaction_Implementation() override { return FactionID; };
    void SetFaction_Implementation(int32 NewFaction) override;

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
    EPawnType PawnType = EPawnType::Villager;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn")
    int32 FactionID = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    TObjectPtr<UDataTable> FactionTable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float AcceptanceDistance = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float CharacterTurnSpeed = 5.0f;

private:
    FVector MoveTargetLocation;
    bool bMoving = false;

    void OrientPawnToMovementDirection();
};
