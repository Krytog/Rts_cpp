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

void UWidgetMinimap::UpdateSize(FVector2D NewSize)
{
	Size = NewSize;
}

FVector2D UWidgetMinimap::GetSize() const
{
	return Size;
}
