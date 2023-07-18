// Krytog, 2023


#include "Buildings/LogisticBuilding.h"
#include "Components/StaticMeshComponent.h"

ALogisticBuilding::ALogisticBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	LogisticFieldComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LogisticFieldMesh"));
	LogisticFieldComponent->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative,
																					   EAttachmentRule::KeepRelative,
																					   EAttachmentRule::KeepWorld,
																					   false));
	LogisticFieldComponent->bUseAttachParentBound = true;
	LogisticFieldComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALogisticBuilding::BeginPlay()
{
	Super::BeginPlay();
	ABuilding::BeginPlay();
	LogisticFieldComponent->SetVisibility(false);
}

void ALogisticBuilding::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	const float ScaleFactor = LogisticFieldRadius / 50.0f;
	const FVector Scale = FVector(ScaleFactor, ScaleFactor, 1.0f);
	LogisticFieldComponent->SetWorldScale3D(Scale);
}

void ALogisticBuilding::Select()
{
	ABuilding::Select();
	LogisticFieldComponent->SetVisibility(true);
}

void ALogisticBuilding::Deselect()
{
	ABuilding::Deselect();
	LogisticFieldComponent->SetVisibility(false);
}

float ALogisticBuilding::GetLogistickRadius() const
{
	return LogisticFieldRadius;
}
