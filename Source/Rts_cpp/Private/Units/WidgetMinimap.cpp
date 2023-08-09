// Krytog, 2023


#include "Units/WidgetMinimap.h"
#include "Components/Image.h"

void UWidgetMinimap::SetImage(UTexture2D* Texture)
{
	Image->SetBrushFromTexture(Texture, true);
}

void UWidgetMinimap::SetColor(FLinearColor Color)
{
	Image->SetColorAndOpacity(Color);
}

void UWidgetMinimap::SetSize(FVector2D NewSize)
{
	Image->SetBrushSize(NewSize);
}
