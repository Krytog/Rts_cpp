// Krytog, 2023

#include "Player/Components/BuildingNetworkComponent.h"
#include "Player/Components/GraphWithPointers.h"
#include "Buildings/Building.h"

// Sets default values for this component's properties
UBuildingNetworkComponent::UBuildingNetworkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildingNetworkComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuildingNetworkComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuildingNetworkComponent::AddBuilding(ABuilding* Building)
{
	Graph.AddVertexToGraph(Building);
	Graph.CalculateComponents();
	Building->ISelectable::OnDestroyed().AddUObject(this, RemoveBuilding);
}

void UBuildingNetworkComponent::RemoveBuilding(const AActor* Building)
{
	Graph.RemoveVertex(Building);
	Graph.CalculateComponents();
}

bool UBuildingNetworkComponent::IsConnected(const ABuilding* First, const ABuilding* Second) const
{
	float FirstRadius = First->GetLogistickRadius();
	float SecondRadius = Second->GetLogistickRadius();
	float Distance = FVector::Distance(First->GetActorLocation(), Second->GetActorLocation());
	return Distance <= FirstRadius || Distance <= SecondRadius;
}

