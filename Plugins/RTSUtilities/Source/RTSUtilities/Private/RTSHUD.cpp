// Real Time Strategy Game. Copyright Taukach K. All Rights Reserved.

#include "RTSHUD.h"

void ARTSHUD::DrawHUD() 
{
    Super::DrawHUD();

    if (bDrawSelectionRect)
    {
        DrawRect(SelectionRectColor, SelectionRectStart.X, SelectionRectStart.Y, SelectionRectSize.X, SelectionRectSize.Y);
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
}