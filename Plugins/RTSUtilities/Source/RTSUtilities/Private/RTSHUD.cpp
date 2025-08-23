// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSHUD.h"
#include "RTSBasePawn.h"
#include "RTSBaseBuilding.h"

void ARTSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (bDrawSelectionRect)
    {
        DrawRect(SelectionRectColor, SelectionRectStart.X, SelectionRectStart.Y, SelectionRectSize.X, SelectionRectSize.Y);
    }
    if (bSelectActors)
    {
        SelectActorsInRect();
    }
}

void ARTSHUD::ShowSelectionRect(const FVector2D InSelectionRectStart, const FVector2D InSelectionRectSize) 
{
    SelectionRectStart = InSelectionRectStart;
    SelectionRectSize = InSelectionRectSize;
    bDrawSelectionRect = true;
}

void ARTSHUD::HideSelectionRect() 
{
    bDrawSelectionRect = false;
    bSelectActors = true;
}

void ARTSHUD::SelectActorsInRect() 
{
    SelectedActors.Empty();

    FVector2D FirstPoint = SelectionRectStart;
    FVector2D SecondPoint = SelectionRectStart + SelectionRectSize;

    TArray<ARTSBasePawn*> SelectedPawns;
    GetActorsInSelectionRectangle<ARTSBasePawn>(FirstPoint, SecondPoint, SelectedPawns, false);

    if (SelectedPawns.Num() > 0)
    {
        bSelectActors = false;

        for (const auto SelectedPawn : SelectedPawns)
        {
            if (SelectedPawn)
            {
                SelectedActors.AddUnique(SelectedPawn);
            }
        }

        return;
    }

    TArray<ARTSBaseBuilding*> SelectedBuildings;
    GetActorsInSelectionRectangle<ARTSBaseBuilding>(FirstPoint, SecondPoint, SelectedBuildings, false);

    if (SelectedBuildings.Num() > 0)
    {
        bSelectActors = false;

        for (const auto SelectedBuilding : SelectedBuildings)
        {
            if (SelectedBuilding)
            {
                SelectedActors.AddUnique(SelectedBuilding);
            }
        }

        return;
    }
}