// Krytog, 2023


#include "Player/MinimapWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Interfaces/MinimapVisible.h"

void UMinimapWidget::AddStaticObject(const IMinimapVisible* Object)
{
	UPanelSlot* PanelSlot = Minimap->AddChild(Object->GetMinimapWidget());
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot);
	CanvasSlot->SetAnchors(FAnchors::FAnchors(0.5f, 0.5f)); // So coordinates will be calculated with respect to widget's center
	CanvasSlot->SetPosition(FVector2D(0.0f, 0.0f));
}

void UMinimapWidget::AddDynamicObject(const IMinimapVisible* Object)
{
	UPanelSlot* PanelSlot = Minimap->AddChild(Object->GetMinimapWidget());
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot);
	CanvasSlot->SetAnchors(FAnchors::FAnchors(0.5f, 0.5f)); // So coordinates will be calculated with respect to widget's center
	CanvasSlot->SetPosition(FVector2D(0.0f, 0.0f));
	DynamicObjects[Object] = CanvasSlot;
}

void UMinimapWidget::RemoveFromMinimap(const IMinimapVisible* Object)
{
	Object->GetMinimapWidget()->RemoveFromParent();
}
