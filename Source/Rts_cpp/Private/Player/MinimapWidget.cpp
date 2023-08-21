// Krytog, 2023


#include "Player/MinimapWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Interfaces/MinimapVisible.h"
#include "Units/WidgetMinimap.h"

UCanvasPanelSlot* UMinimapWidget::CoreAddObject(const IMinimapVisible* Object)
{
	UPanelSlot* PanelSlot = Minimap->AddChild(Object->GetWidgetMinimap());
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PanelSlot);
	CanvasSlot->SetAutoSize(true);
	return CanvasSlot;
}

void UMinimapWidget::PlaceOnMinimap(const class IMinimapVisible* Object, class UCanvasPanelSlot* CanvasSlot) const
{
	const FVector2D WorldCoordinates = Object->GetObjectCoordinates();
	const float RelativeX = 0.5f + WorldCoordinates.X / MapWidth;
	const float RelativeY = 0.5f - WorldCoordinates.Y / MapHeight;
	FAnchors Anchors;
	Anchors.Minimum = FVector2D(RelativeX, RelativeY);
	Anchors.Maximum = Anchors.Minimum;
	CanvasSlot->SetAnchors(Anchors);
}

void UMinimapWidget::AddStaticObject(const IMinimapVisible* Object)
{
	UCanvasPanelSlot* CanvasSlot = CoreAddObject(Object);
	PlaceOnMinimap(Object, CanvasSlot);
}

void UMinimapWidget::AddDynamicObject(const IMinimapVisible* Object)
{
	UCanvasPanelSlot* CanvasSlot = CoreAddObject(Object);
	PlaceOnMinimap(Object, CanvasSlot);
	DynamicObjects.Add(Object, CanvasSlot);
}

void UMinimapWidget::RemoveFromMinimap(const IMinimapVisible* Object)
{
	Object->GetWidgetMinimap()->RemoveFromParent();
}

void UMinimapWidget::UpdateObjectsLocation()
{
	for (auto& [Object, CanvasSlot] : DynamicObjects)
	{
		PlaceOnMinimap(Object, CanvasSlot);
	}
}

void UMinimapWidget::SetMapSize(FVector2D NewSize)
{
	MapWidth = NewSize.X;
	MapHeight = NewSize.Y;
}
