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
	CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	return CanvasSlot;
}

void UMinimapWidget::PlaceOnMinimap(const class IMinimapVisible* Object, class UCanvasPanelSlot* CanvasSlot) const
{
	// Setting actual position
	const FVector2D WorldCoordinates = Object->GetObjectCoordinates();
	const float RelativeX = 0.5f + WorldCoordinates.X / MapWidth;
	const float RelativeY = 0.5f - WorldCoordinates.Y / MapHeight;
	FAnchors Anchors;
	Anchors.Minimum = FVector2D(RelativeX, RelativeY);
	Anchors.Maximum = Anchors.Minimum;
	CanvasSlot->SetAnchors(Anchors);

	// Setting actual size
	const UWidgetMinimap* Widget = Object->GetWidgetMinimap();
	const FVector2D DesiredSize = Widget->GetSize();
	CanvasSlot->SetSize(DesiredSize);
}

void UMinimapWidget::RemoveDestroyedObject(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	IMinimapVisible* MinimapVisible = Cast<IMinimapVisible>(Actor);
	MinimapVisible->OnEndPlayEvent().RemoveDynamic(this, &UMinimapWidget::RemoveDestroyedObject);
	RemoveFromMinimap(MinimapVisible);
	DynamicObjects.Remove(MinimapVisible);
}

void UMinimapWidget::AddStaticObject(IMinimapVisible* Object)
{
	UCanvasPanelSlot* CanvasSlot = CoreAddObject(Object);
	Object->OnEndPlayEvent().AddDynamic(this, &UMinimapWidget::RemoveDestroyedObject);
	PlaceOnMinimap(Object, CanvasSlot);
}

void UMinimapWidget::AddDynamicObject(IMinimapVisible* Object)
{
	UCanvasPanelSlot* CanvasSlot = CoreAddObject(Object);
	Object->OnEndPlayEvent().AddDynamic(this, &UMinimapWidget::RemoveDestroyedObject);
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
