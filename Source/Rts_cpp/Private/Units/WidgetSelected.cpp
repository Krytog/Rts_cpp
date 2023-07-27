// Krytog, 2023


#include "Units/WidgetSelected.h"
#include "Components/Image.h"

void UWidgetSelected::BindToUnit(AActor* UnitToBind)
{
	Unit = UnitToBind;
}

AActor* UWidgetSelected::GetBindedUnit() const
{
	return Unit;
}

void UWidgetSelected::SetIconImage(UTexture2D* Image)
{
	IconSelected->SetBrushFromTexture(Image);
}