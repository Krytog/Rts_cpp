// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingNetworkAgentComponent.generated.h"

class UBuildingNetworkComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBuildingNetworkAgentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingNetworkAgentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void InsertInNetwork(UBuildingNetworkComponent* Network);

protected:
	UPROPERTY()
	UBuildingNetworkComponent* BuildingNetwork;
};
