// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingNetworkComponent.generated.h"

class ABuilding;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBuildingNetworkComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingNetworkComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddBuilding(ABuilding* Building);
	void RemoveBuilding(const AActor* Building);

private:
	bool IsConnected(const ABuilding* First, const ABuilding* Second) const;

	class FGraphWithPointers Graph;
};
