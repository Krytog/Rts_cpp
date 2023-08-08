// Krytog, 2023

#include "Player/Components/BuildingNetworkComponent.h"
#include "Player/Components/GraphWithPointers.h"
#include "Buildings/Building.h"
#include "Buildings/LogisticBuilding.h"

// Sets default values for this component's properties
UBuildingNetworkComponent::UBuildingNetworkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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

void UBuildingNetworkComponent::AddBuilding(ABuilding* Building)
{
	Building->OnEndPlayEvent().AddDynamic(this, &UBuildingNetworkComponent::RemoveDestroyedBuilding);
	Buildings.Add(Building);
	Graph.AddVertexToGraph(Building);
	CalculateConnections(Building);
	Graph.CalculateComponents();
}

void UBuildingNetworkComponent::RemoveBuilding(ABuilding* Building)
{
	Graph.RemoveVertex(Building);
	Buildings.RemoveSingleSwap(Building);
	Graph.CalculateComponents();
}

int32 UBuildingNetworkComponent::GetComponentOf(const ABuilding* Building) const
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
			if (Graph.IsConnectedDirected(Building, OtherBuilding))
			{
				const FVector Offset = 0.15f * (Building->GetActorLocation() - OtherBuilding->GetActorLocation());
				DrawDebugDirectionalArrow(GetWorld(), Building->GetActorLocation(), OtherBuilding->GetActorLocation() + Offset, 500.0f, FColor::Emerald);
			}
		}
	}
}

bool UBuildingNetworkComponent::IsToBeConnected(const ABuilding* First, const ABuilding* Second) const
{
	const float FirstRadius = First->GetLogistickRadius();
	const float SecondRadius = Second->GetLogistickRadius();
	const float Distance = FVector::Distance(First->GetActorLocation(), Second->GetActorLocation());
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

void UBuildingNetworkComponent::RemoveDestroyedBuilding(AActor* Object, EEndPlayReason::Type EndPlayReason)
{
	RemoveBuilding(Cast<ABuilding>(Object));
}

void UBuildingNetworkComponent::EnableBuildingPlacementMode(bool bEnabled) const
{
	for (ABuilding* const Building : Buildings)
	{
		if (ALogisticBuilding* const LogisticBuilding = Cast<ALogisticBuilding>(Building))
		{
			LogisticBuilding->SetLogisticFieldVisibility(bEnabled);
		}
	}
}

bool UBuildingNetworkComponent::IsInsideLogisticArea(const FVector& ObjectLocation) const
{
	for (const auto* const Building : Buildings)
	{
		const float DistanceSquared = FVector::DistSquared(Building->GetActorLocation(), ObjectLocation); // It's faster for obvious reasons
		const float Radius = Building->GetLogistickRadius();
		if (DistanceSquared <= Radius * Radius)
		{
			return true;
		}
	}
	return false;
}
