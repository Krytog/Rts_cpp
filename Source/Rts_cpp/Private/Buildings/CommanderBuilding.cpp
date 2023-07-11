// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/CommanderBuilding.h"
#include "Buildings/Components/ArrowToTargetComponent.h"

ACommanderBuilding::ACommanderBuilding()
{
	ArrowComponent = CreateDefaultSubobject<UArrowToTargetComponent>(TEXT("ArrowComponent"));
	PrimaryActorTick.bCanEverTick = true;
}

void ACommanderBuilding::SetTargetLocation(const FVector& Location)
{
	ArrowComponent->SetTargetLocation(Location);
	ArrowComponent->SetArrowVisibility(true);
}

void ACommanderBuilding::SetTarget(AActor* Target)
{
	ArrowComponent->SetTarget(Target);
	ArrowComponent->SetArrowVisibility(true);
}

TOptional<FVector> ACommanderBuilding::GetTargetLocation() const
{
	return ArrowComponent->GetTargetLocation();
}

void ACommanderBuilding::ResetTarget()
{
	ArrowComponent->ResetTarget();
}

void ACommanderBuilding::Select()
{
	ABuilding::Select();
	if (ArrowComponent->IsTargetSet())
	{
		ArrowComponent->SetArrowVisibility(true);
	}
}

void ACommanderBuilding::Deselect()
{
	ABuilding::Deselect();
	ArrowComponent->SetArrowVisibility(false);
}

void ACommanderBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACommanderBuilding::BeginPlay()
{
	Super::BeginPlay();
}
