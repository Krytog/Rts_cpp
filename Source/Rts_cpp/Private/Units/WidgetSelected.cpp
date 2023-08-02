// Krytog, 2023


#include "Units/WidgetSelected.h"
#include "Units/Unit.h"
#include "Components/Image.h"
#include "Player/DefaultPlayer.h"

FReply UWidgetSelected::NativeOnMouseButtonDown(const FGeometry &Geometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		ADefaultPlayer* Player = Cast<ADefaultPlayer>(GetOwningPlayer()->GetPawn());
		if (Player)
		{
			TArray<AUnit*> NewSelectedObjects;
			NewSelectedObjects.Add(Unit);
			Player->UpdateSelectedObjects(NewSelectedObjects);
		}
	}
	return FReply::Handled();
}

void UWidgetSelected::BindToUnit(AUnit* UnitToBind)
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

UWidgetSelected::FEventRemovedFromParent& UWidgetSelected::OnRemovedFromParent()
{
	return EventRemovedFromParent;
}

void UWidgetSelected::RemoveFromParentNotified()
{
	RemoveFromParent();
	EventRemovedFromParent.Broadcast(this);
}
