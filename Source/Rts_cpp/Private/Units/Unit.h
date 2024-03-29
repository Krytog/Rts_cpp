// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/MinimapVisible.h"
#include "Unit.generated.h"

UCLASS(hidecategories = ("Physics", "Cooking", "Replication", "Rendering", "WorldPartition", "HLOD", "Collision", "Events", "DataLayers", "Input", "Actor", "Actor Tick"))
class AUnit : public AActor, public ISelectable, public IMinimapVisible 
{
	GENERATED_BODY()
	
public:	
	AUnit();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual FActorEndPlaySignature& OnEndPlayEvent() override;

	// ISelectable overrides

	virtual void Select() override;
	virtual void Deselect() override;
	virtual bool IsSelected() const override;
	virtual int32 GetTeamId() const override;
	virtual bool IsInTeamWithId(int32 TeamIdToCheck) const override;
	virtual FText GetInfoName() const override;
	virtual int32 GetPriority() const override;
	class UWidgetSelected* GetWidgetSelected() const override;

	// IMinimapVisible overrides
	UFUNCTION(BlueprintCallable)
	virtual void RegisterOnMinimap(class ADefaultPlayer* Player) override;
	virtual FVector2D GetObjectCoordinates() const override;
	virtual class UWidgetMinimap* GetWidgetMinimap() const override;


	virtual void SetTeamId(int32 NewTeamId);

	friend uint32 GetTypeHash(const AUnit* Unit);

protected:
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

	/* Class for widget that will be used for displaying this unit on the minimap*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Minimap|Widget")
	TSubclassOf<class UWidgetMinimap> WidgetMinimapClass;

	/* Image for displaying this unit on the minimap */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Minimap|Widget")
	class UTexture2D* IconMinimap;

	/* Size of the image on the minimap */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Minimap|Widget")
	FVector2D IconMinimapSize;

	UPROPERTY()
	class UWidgetMinimap* WidgetMinimap = nullptr;

	/* Name of this unit which will be displayed in different UIs */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Name")
	FText InfoName;

private:
	void InitWidgetMinimap();
	void InitWidgetSelected();

	void DeleteWidgetMinimap();
	void DeleteWidgeSelected();
};
