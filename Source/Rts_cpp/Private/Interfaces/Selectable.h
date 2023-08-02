// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_CPP_API ISelectable
{
	GENERATED_BODY()

public:
	// Functions that affect visual state of object. Enables/disables selection decal, arrows to target, etc 
	virtual void Select() = 0;
	virtual void Deselect() = 0;
	virtual bool IsSelected() const = 0;

	// Functions for handling belongings to a team
	virtual int32 GetTeamId() const = 0;
	virtual bool IsInTeamWithId(int32 TeamId) const = 0;

	// Functions for UI handling when selected
	virtual class UWidgetSelected* GetWidgetSelected() const = 0;
	virtual int32 GetPriority() const = 0;

	// Functions for getting object's info
	virtual FText GetInfoName() const = 0;

	DECLARE_EVENT_OneParam(ISelectable, FDestroyedEvent, const ISelectable*);
	FDestroyedEvent& OnDestroyed();

protected:
	void NotifyThatDestroyed();

private:
	FDestroyedEvent DestroyedEvent;
};
