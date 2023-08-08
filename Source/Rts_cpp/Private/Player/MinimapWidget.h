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
	void AddStaticObject(const class IMinimapVisible* Object);
	void AddDynamicObject(const class IMinimapVisible* Object);
	void RemoveFromMinimap(const class IMinimapVisible* Object);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* Minimap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Background;

private:
	TMap<const class IMinimapVisible*, class UCanvasPanelSlot*> DynamicObjects;

	uint32 MapWidth = 1000;
	uint32 MapHeight = 1000;
};
