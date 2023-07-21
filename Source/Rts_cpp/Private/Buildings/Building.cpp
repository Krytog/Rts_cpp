// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Components/StaticMeshComponent.h"
#include "Player/DefaultPlayer.h"
#include "Buildings/Components/BuildingNetworkAgentComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = MeshComponent;

	SelectionDecalComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionMesh"));
	SelectionDecalComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SelectionDecalComponent->SetVisibility(false);
	SelectionDecalComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SelectionDecalComponent->bUseAttachParentBound = true;

	BuildingNetworkAgentComponent = CreateDefaultSubobject<UBuildingNetworkAgentComponent>(TEXT("BuildingNetworkAgent"));

	InfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidgetComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	InfoWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABuilding::Select()
{
	bSelected = true;
	SelectionDecalComponent->SetVisibility(true);
}

void ABuilding::Deselect()
{
	bSelected = false;
	SelectionDecalComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	SelectionDecalComponent->SetVisibility(false);
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	NotifyThatDestroyed();
}

bool ABuilding::IsSelected() const
{
	return bSelected;
}

float ABuilding::GetLogistickRadius() const
{
	return 0.0f;
}

void ABuilding::BindToPlayer(ADefaultPlayer* Player) const
{
	UBuildingNetworkComponent* BuildingNetwork = Player->GetBuildingNetwork();
	BuildingNetworkAgentComponent->InsertInNetwork(BuildingNetwork);
}

