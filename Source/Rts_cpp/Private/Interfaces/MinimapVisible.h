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
	virtual void RegisterAtMinimap(class ADefaultPlayer* Player) const = 0;

	virtual FVector2D GetObjectCoordinates() const = 0;
	virtual class UWidgetMinimap* GetWidgetMinimap() const = 0;

	virtual FActorEndPlaySignature& OnEndPlayEvent() = 0;

	friend uint32 GetTypeHash(const IMinimapVisible* Object);
	bool operator==(const IMinimapVisible* Object) const;
};
