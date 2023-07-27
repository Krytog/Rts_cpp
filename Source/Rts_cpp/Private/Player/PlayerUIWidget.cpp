// Krytog, 2023


#include "Player/PlayerUIWidget.h"
#include "Components/HorizontalBox.h"
#include "Units/WidgetSelected.h"

void UPlayerUIWidget::AddSelectedUnitWidget(UWidgetSelected* Widget)
{
	Widget->OnRemovedFromParent().AddUObject(this, &UPlayerUIWidget::RemoveSelectedUintWidget);
	int32 AddedSelectedUnitsWidgetsCount = SelectionLayer1->GetChildrenCount();
	AddedSelectedUnitsWidgetsCount += SelectionLayer2->GetChildrenCount();
	AddedSelectedUnitsWidgetsCount += SelectionLayer3->GetChildrenCount();
	AddSelectedUintWidgetToCorrespondingLayer(Widget, AddedSelectedUnitsWidgetsCount);
}

void UPlayerUIWidget::RemoveSelectedUintWidget(UWidgetSelected* Widget)
{
	Widget->OnRemovedFromParent().RemoveAll(this);

	// Now we need to rebuild all layers
	TArray<UWidget*> Widgets = SelectionLayer1->GetAllChildren();
	Widgets += SelectionLayer2->GetAllChildren();
	Widgets += SelectionLayer3->GetAllChildren();
	SelectionLayer1->ClearChildren();
	SelectionLayer2->ClearChildren();
	SelectionLayer3->ClearChildren();
	for (int32 i = 0; i < Widgets.Num(); ++i)
	{
		AddSelectedUintWidgetToCorrespondingLayer(Widgets[i], i);
	}
}

void UPlayerUIWidget::AddSelectedUintWidgetToCorrespondingLayer(UWidget* Widget, int32 AlreadyIn)
{
	if (AlreadyIn == 24)
	{
		return;
	}
	if (AlreadyIn < 8)
	{
		SelectionLayer1->AddChild(Widget);
	}
	else if (AlreadyIn < 16)
	{
		SelectionLayer2->AddChild(Widget);
	}
	else
	{
		SelectionLayer3->AddChild(Widget);
	}
}
