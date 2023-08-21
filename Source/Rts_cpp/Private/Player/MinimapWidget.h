// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

/**
 * 
 */

UCLASS()
class UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/* Adds an object whose location won't be updated */
	void AddStaticObject(const class IMinimapVisible* Object);

	/* Adds an object whose location will be updated when UpdateObjectsLocation is called */
	void AddDynamicObject(const class IMinimapVisible* Object);

	/* Removes an object from this minimap */
	void RemoveFromMinimap(const class IMinimapVisible* Object);

	/* Updates all rigstered dynamic object locations. Has O(dynamic objects count) perfomance */
	void UpdateObjectsLocation();

	/* Sets Map Size that will be used to calculate realtive positions on the minimap */
	void SetMapSize(FVector2D NewSize);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* Minimap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Background;

private:
	TMap<const class IMinimapVisible*, class UCanvasPanelSlot*> DynamicObjects;

	/* Adds an object to the underlying canvas and does basic setup */
	class UCanvasPanelSlot* CoreAddObject(const class IMinimapVisible* Object);

	/* Places an object icon on the minimap based on the posisiton in the game world. This object should be already added to the canvas */
	void PlaceOnMinimap(const class IMinimapVisible* Object, class UCanvasPanelSlot* CanvasSlot) const;

	float MapWidth = 4000.0f;
	float MapHeight = 4000.0f;
};
