// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Components/StaticMeshComponent.h"

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
	SelectionDecalComponent->bUseAttachParentBound = true;
}

void ABuilding::OnSelect()
{
	bSelected = true;
	SelectionDecalComponent->SetVisibility(true);
}

void ABuilding::OnDeselect()
{
	bSelected = false;
	SelectionDecalComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MeshComponent->SetStaticMesh(Mesh);
	SelectionDecal->SetMaterial(0, DecalMaterial);
	SelectionDecalComponent->SetStaticMesh(SelectionDecal);
	SelectionDecalComponent->SetVisibility(bSelected);
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABuilding::IsSelected() const
{
	return bSelected;
}

