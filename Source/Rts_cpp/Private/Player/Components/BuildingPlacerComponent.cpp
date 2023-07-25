// Krytog, 2023


#include "Player/Components/BuildingPlacerComponent.h"
#include "Buildings/Building.h"
#include "Player/DefaultPlayer.h"
#include "Player/Components/BuildingNetworkComponent.h"

// Sets default values for this component's properties
UBuildingPlacerComponent::UBuildingPlacerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}


// Called when the game starts
void UBuildingPlacerComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayer = Cast<ADefaultPlayer>(GetOwner());
	check(OwningPlayer);
	PlayerBuildingNetwork = OwningPlayer->GetBuildingNetwork();
	check(PlayerBuildingNetwork);
}


// Called every frame
void UBuildingPlacerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	BuildingToBePlaced->SetActorLocation(OwningPlayer->GetLocationUnderCursor());
	bool bIsInsideLogisticArea = PlayerBuildingNetwork->IsInsideLogisticArea(BuildingToBePlaced->GetActorLocation());
	bool bCouldBePlaced = BuildingToBePlaced->CanBePlaced();
	if (bIsInsideLogisticArea)
	{
		BuildingToBePlaced->RemovePlacementFlag(EPlacementFlags::NoLogistic);
		if (!bCouldBePlaced && BuildingToBePlaced->CanBePlaced()) // We couldn't place the building, but now we can, therefore need to change materials
		{
			BuildingToBePlaced->SetAppropriatePlacementMaterial();
		}
	}
	else
	{
		BuildingToBePlaced->AddPlacementFlag(EPlacementFlags::NoLogistic);
		if (bCouldBePlaced && !BuildingToBePlaced->CanBePlaced()) // We could place the building, but now we cannot, therefore need to change materials
		{
			BuildingToBePlaced->SetAppropriatePlacementMaterial();
		}
	}
}

void UBuildingPlacerComponent::StartPlacingBuilding(TSubclassOf<ABuilding> BuildingClass)
{
	BuildingToBePlaced = GetWorld()->SpawnActor<ABuilding>(BuildingClass);
	check(BuildingToBePlaced);
	bool bIsInsideLogisticArea = PlayerBuildingNetwork->IsInsideLogisticArea(OwningPlayer->GetLocationUnderCursor());
	if (bIsInsideLogisticArea)
	{
		BuildingToBePlaced->RemovePlacementFlag(EPlacementFlags::NoLogistic);
	}
	else
	{
		BuildingToBePlaced->AddPlacementFlag(EPlacementFlags::NoLogistic);
	}
	BuildingToBePlaced->SetAppropriatePlacementMaterial();
	PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UBuildingPlacerComponent::CancelPlacingBuilding()
{
	if (!BuildingToBePlaced)
	{
		return;
	}
	GetWorld()->DestroyActor(BuildingToBePlaced);
	PrimaryComponentTick.SetTickFunctionEnable(false);
	BuildingToBePlaced = nullptr;
}

bool UBuildingPlacerComponent::TryPlaceBuilding()
{
	bool bWasPlaced = BuildingToBePlaced->TryPlace();
	if (bWasPlaced)
	{
		PrimaryComponentTick.SetTickFunctionEnable(false);
		BuildingToBePlaced->BindToPlayer(OwningPlayer);
		BuildingToBePlaced = nullptr;
	}
	return bWasPlaced;
}

