// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Unit.generated.h"

UCLASS(hidecategories = ("Physics", "Cooking", "Replication", "Rendering", "WorldPartition", "HLOD", "Collision", "Events", "DataLayers", "Input", "Actor", "Actor Tick"))
class AUnit : public AActor, public ISelectable
{
	GENERATED_BODY()
	
public:	
	AUnit();

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	virtual void Select() override;
	virtual void Deselect() override;
	virtual bool IsSelected() const override;
	virtual int32 GetTeamId() const override;
	virtual bool IsInTeamWithId(int32 TeamIdToCheck) const override;

	virtual FText GetInfoName() const override;
	virtual int32 GetPriority() const override;

	virtual void SetTeamId(int32 NewTeamId);

	friend uint32 GetTypeHash(const AUnit* Unit);

	virtual FActorEndPlaySignature& OnEndPlayEvent() override;

protected:
	virtual void BeginPlay() override;

	int32 TeamId = -1;

	/* Class for widget that will be used in player UI selection panel*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Selected|Widget")
	TSubclassOf<class UWidgetSelected> WidgetSelectedClass;

	/* Image for widget that will be used in player UI selection Panel*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Selected|Widget")
	class UTexture2D* IconSelected;

	UPROPERTY()
	class UWidgetSelected* WidgetSelected = nullptr;

	/* Priority in group of selected units. Units with higher number have greater priority */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Selected|Priority", meta=(DisplayName="Priority"))
	int32 SelectionPriority = 0;

public:	
	virtual void Tick(float DeltaTime) override;

	class UWidgetSelected* GetWidgetSelected() const override;
};
