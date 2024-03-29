// Krytog, 2023


#include "Buildings/Components/BuildingNetworkAgentComponent.h"
#include "Player/Components/BuildingNetworkComponent.h"
#include "Buildings/Building.h"

// Sets default values for this component's properties
UBuildingNetworkAgentComponent::UBuildingNetworkAgentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildingNetworkAgentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBuildingNetworkAgentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuildingNetworkAgentComponent::InsertInNetwork(UBuildingNetworkComponent* Network)
{
	BuildingNetwork = Network;
	ABuilding* Building = Cast<ABuilding>(GetOwner());
	BuildingNetwork->AddBuilding(Building);
}

