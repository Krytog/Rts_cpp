// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MinimapVisible.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMinimapVisible : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IMinimapVisible
{
	GENERATED_BODY()

public:
	/* Register this object on the minimap of given player */
	virtual void RegisterOnMinimap(class ADefaultPlayer* Player) const = 0;

	/* Returns 2D coordinates of the object that are used for displaying object on the minimap*/
	virtual FVector2D GetObjectCoordinates() const = 0;

	/* Returns Widget that is displayed on the minimap*/
	virtual class UWidgetMinimap* GetWidgetMinimap() const = 0;

	/* Returns delegate that is fired when this object ends play */
	virtual FActorEndPlaySignature& OnEndPlayEvent() = 0;

	friend uint32 GetTypeHash(const IMinimapVisible* Object);
	bool operator==(const IMinimapVisible* Object) const;
};
