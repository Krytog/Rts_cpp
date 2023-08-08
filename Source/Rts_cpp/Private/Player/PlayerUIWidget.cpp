// Krytog, 2023


#include "Player/PlayerUIWidget.h"
#include "Components/HorizontalBox.h"
#include "Units/WidgetSelected.h"
#include "Components/HorizontalBoxSlot.h"
#include "Units/Unit.h"

void UPlayerUIWidget::AddSelectedUnitWidget(UWidgetSelected* Widget)
{
	Widget->OnRemovedFromParent().AddUObject(this, &UPlayerUIWidget::RemoveSelectedUnitWidget);
	int32 AddedSelectedUnitsWidgetsCount = SelectionLayer1->GetChildrenCount();
	AddedSelectedUnitsWidgetsCount += SelectionLayer2->GetChildrenCount();
	AddedSelectedUnitsWidgetsCount += SelectionLayer3->GetChildrenCount();
	AddSelectedUintWidgetToCorrespondingLayer(Widget, AddedSelectedUnitsWidgetsCount);
}

void UPlayerUIWidget::RemoveSelectedUnitWidget(UWidgetSelected* Widget)
{
	Widget->OnRemovedFromParent().RemoveAll(this);

	// Now we need to rebuild all layers, but we don't need to reodred them, as after removing a widget the relative order of others is maintained
	RebuildSelectedUnitWidgets();
}

void UPlayerUIWidget::ReorderSelectedUnitWidgets(const TSet<class AUnit*>& SelectedObjects)
{
	SelectionLayer1->ClearChildren();
	SelectionLayer2->ClearChildren();
	SelectionLayer3->ClearChildren();
	int32 Count = 0;
	for (auto Unit : SelectedObjects)
	{
		AddSelectedUintWidgetToCorrespondingLayer(Unit->GetWidgetSelected(), Count);
		++Count;
	}
}

void UPlayerUIWidget::RebuildSelectedUnitWidgets()
{
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
	if (AlreadyIn == 36)
	{
		return;
	}
	UPanelSlot* InLayerSlot;
	if (AlreadyIn < 12)
	{
		InLayerSlot = SelectionLayer1->AddChild(Widget);
	}
	else if (AlreadyIn < 24)
	{
		InLayerSlot = SelectionLayer2->AddChild(Widget);
	}
	else
	{
		InLayerSlot = SelectionLayer3->AddChild(Widget);
	}
	Cast<UHorizontalBoxSlot>(InLayerSlot)->SetPadding(FMargin(5.0f, 0.0f));
}
