// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UPlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UMinimapWidget* Minimap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UImage* OrdersPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UHorizontalBox* SelectionLayer1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UHorizontalBox* SelectionLayer2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UHorizontalBox* SelectionLayer3;

public:
	void AddSelectedUnitWidget(class UWidgetSelected* Widget);

	void RemoveSelectedUnitWidget(class UWidgetSelected* Widget);

	/* This function will completely rebuild SelectedUnitsPanel according to current order of SelectedObject */
	void ReorderSelectedUnitWidgets(const TSet<class AUnit*>& SelectedObjects);

	/* This function will rebuild SelectedUnitsPanel maintaining their relative order */
	void RebuildSelectedUnitWidgets();

	class UMinimapWidget* GetMinimap() const;

private:
	void AddSelectedUintWidgetToCorrespondingLayer(class UWidget* Widget, int32 AlreadyIn);
};
