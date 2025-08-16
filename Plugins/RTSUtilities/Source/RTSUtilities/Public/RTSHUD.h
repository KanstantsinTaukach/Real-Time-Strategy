// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHUD.generated.h"

class ARTSBasePawn;

UCLASS()
class RTSUTILITIES_API ARTSHUD : public AHUD
{
    GENERATED_BODY()

private:
    bool bDrawSelectionRect = false;

    FVector2D SelectionRectStart;
    FVector2D SelectionRectSize;

    FLinearColor SelectionRectColor = FLinearColor(0.0f, 1.0f, 0.0f, 0.3f);

    bool bSelectActors = false;
    TArray<ARTSBasePawn*> SelectedActors;

    void SelectActorsInRect();

protected:
    virtual void DrawHUD() override;

public:
    void ShowSelectionRect(const FVector2D InSelectionRectStart, const FVector2D InSelectionRectSize);
    void HideSelectionRect();

    TArray<ARTSBasePawn*> GetSelectedActors() const { return SelectedActors; };
};
