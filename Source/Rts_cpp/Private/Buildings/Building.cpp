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
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

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

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::OverlapBegin);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &ABuilding::OverlapEnd);
}

void ABuilding::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OverlappedActors)
	{
		bool bCouldBePlaced = CanBePlaced();
		AddPlacementFlag(EPlacementFlags::PositionBlocked);
		if (bCouldBePlaced && !CanBePlaced())
		{
			SetAppropriatePlacementMaterial();
		}
	}
	++OverlappedActors;
}

void ABuilding::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	--OverlappedActors;
	if (!OverlappedActors)
	{
		bool bCouldBePlaced = CanBePlaced();
		RemovePlacementFlag(EPlacementFlags::PositionBlocked);
		if (!bCouldBePlaced && CanBePlaced())
		{
			SetAppropriatePlacementMaterial();
		}
	}
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

FText ABuilding::GetInfoName() const
{
	return InfoName;
}

void ABuilding::SetAppropriatePlacementMaterial()
{
	if (HasPlacementFlag(EPlacementFlags::AlreadyPlaced))
	{
		return;
	}
	ABuilding* CDO = Cast<ABuilding>(GetClass()->GetDefaultObject());
	check(CDO);
	const auto& InitialMaterials = CDO->MeshComponent->GetMaterials();
	const int32 MaterialsNum = InitialMaterials.Num();
	if (CanBePlaced())
	{
		for (int32 i = 0; i < MaterialsNum; ++i)
		{
			MeshComponent->SetMaterial(i, MaterialPlacementGood);
		}
	}
	else
	{
		for (int32 i = 0; i < MaterialsNum; ++i)
		{
			MeshComponent->SetMaterial(i, MaterialPlacementBad);
		}
	}
}

bool ABuilding::TryPlace()
{
	if (!CanBePlaced())
	{
		return false;
	}
	ABuilding* CDO = Cast<ABuilding>(GetClass()->GetDefaultObject());
	check(CDO);
	const auto& InitialMaterials = CDO->MeshComponent->GetMaterials();
	const int32 MaterialsNum = InitialMaterials.Num();
	for (int32 i = 0; i < MaterialsNum; ++i)
	{
		MeshComponent->SetMaterial(i, InitialMaterials[i]);
	}
	PlacementFlags = uint8(EPlacementFlags::AlreadyPlaced);

	// They're placed and we no longer need to handle their overlappings
	MeshComponent->OnComponentBeginOverlap.Clear();
	MeshComponent->OnComponentEndOverlap.Clear();

	return true;
}

uint8 ABuilding::GetPlacementFlags() const
{
	return PlacementFlags;
}

bool ABuilding::CanBePlaced() const
{
	return PlacementFlags == uint8(EPlacementFlags::CanBePlaced);
}

void ABuilding::AddPlacementFlag(EPlacementFlags Flag)
{
	PlacementFlags |= uint8(Flag);
}

void ABuilding::RemovePlacementFlag(EPlacementFlags Flag)
{
	PlacementFlags &= (~uint8(Flag));
}

bool ABuilding::HasPlacementFlag(EPlacementFlags Flag) const
{
	return PlacementFlags & uint8(Flag);
}
