// Krytog, 2023


#include "Player/PlayerUIWidget.h"
#include "Components/HorizontalBox.h"
#include "Units/WidgetSelected.h"

void UPlayerUIWidget::AddSelectedUnitWidget(UWidgetSelected* Widget)
{
	SelectionPanel->AddChild(Widget);
}
