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
	DrawDebugGraphConnections();
}

void UBuildingNetworkComponent::AddBuilding(AActor* Building)
{
	ABuilding* BuildingCasted = Cast<ABuilding>(Building);
	if (!BuildingCasted)
	{
		return;
	}
	BuildingCasted->ISelectable::OnDestroyed().AddUObject(this, &UBuildingNetworkComponent::RemoveBuilding);
	Buildings.Add(BuildingCasted);
	Graph.AddVertexToGraph(Building);
	CalculateConnections(BuildingCasted);
	Graph.CalculateComponents();
}

void UBuildingNetworkComponent::RemoveBuilding(const AActor* Building)
{
	Graph.RemoveVertex(Building);
	Buildings.RemoveSingleSwap(Cast<ABuilding>(const_cast<AActor*>(Building))); // It's a bad practice
	Graph.CalculateComponents();
}

int32 UBuildingNetworkComponent::GetComponentOf(const AActor* Building) const
{
	return Graph.GetComponentOf(Building);
}

void UBuildingNetworkComponent::DrawDebugGraphConnections() const
{
	for (const AActor* const Building : Buildings)
	{
		for (const AActor* const OtherBuilding : Buildings)
		{
			if (Building == OtherBuilding)
			{
				continue;
			}
			if (Graph.IsConnected(Building, OtherBuilding))
			{
				DrawDebugLine(GetWorld(), Building->GetActorLocation(), OtherBuilding->GetActorLocation(), FColor::Emerald);
			}
		}
	}
}

bool UBuildingNetworkComponent::IsToBeConnected(const ABuilding* First, const ABuilding* Second) const
{
	float FirstRadius = First->GetLogistickRadius();
	float SecondRadius = Second->GetLogistickRadius();
	float Distance = FVector::Distance(First->GetActorLocation(), Second->GetActorLocation());
	return Distance <= FirstRadius || Distance <= SecondRadius;
}

void UBuildingNetworkComponent::CalculateConnections(const ABuilding* Building)
{
	for (const ABuilding* const OtherBuilding : Buildings)
	{
		if (IsToBeConnected(Building, OtherBuilding))
		{
			Graph.ConnectVertices(Building, OtherBuilding);
		}
	}
}

