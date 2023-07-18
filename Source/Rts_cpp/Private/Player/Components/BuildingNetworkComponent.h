// Krytog, 2023

#pragma once

#include "GraphWithPointers.h"

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
	
	void AddBuilding(AActor* Building);
	void RemoveBuilding(const AActor* Building);

	int32 GetComponentOf(const AActor* Building) const;

	void DrawDebugGraphConnections() const;

private:
	bool IsToBeConnected(const ABuilding* First, const ABuilding* Second) const;
	void CalculateConnections(const ABuilding* Building);

	class FGraphWithPointers Graph;

	UPROPERTY()
	TArray<ABuilding*> Buildings;
};