// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingPlacerComponent.generated.h"

class ABuilding;
class ADefaultPlayer;
class UBuildingNetworkComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBuildingPlacerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingPlacerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartPlacingBuilding(TSubclassOf<ABuilding> BuildingClass);
	void CancelPlacingBuilding();
	
	// Returns whether the building was placed
	bool TryPlaceBuilding();

private:
	ABuilding* BuildingToBePlaced = nullptr;
	ADefaultPlayer* OwningPlayer = nullptr;
	UBuildingNetworkComponent* PlayerBuildingNetwork = nullptr;
};
