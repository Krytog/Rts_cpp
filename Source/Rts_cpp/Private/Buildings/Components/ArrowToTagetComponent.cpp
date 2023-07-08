// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/Components/ArrowToTagetComponent.h"
#include "Buildings/ArrowToTarget.h"

// Sets default values for this component's properties
UArrowToTagetComponent::UArrowToTagetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UArrowToTagetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->DestroyActor(ArrowActor);
}

// Called when the game starts
void UArrowToTagetComponent::BeginPlay()
{
	Super::BeginPlay();
	ArrowActor = GetWorld()->SpawnActor<AArrowToTarget>(ArrowClass);
	ArrowActor->SetVisibility(false);
}

void UArrowToTagetComponent::SetTargetLocation(const FVector& Location)
{
	TargetLocation = Location;
	bTargetLocationSet = true;
	ArrowActor->MakePointingTo(GetOwner()->GetActorLocation(), Location);
}

TOptional<FVector> UArrowToTagetComponent::GetTargetLocation()
{
	if (!bTargetLocationSet)
	{
		return NullOpt;
	}
	return TargetLocation;
}

void UArrowToTagetComponent::ResetTargetLocation()
{
	bTargetLocationSet = false;
	ArrowActor->SetVisibility(false);
}

void UArrowToTagetComponent::SetArrowVisibility(bool bNewVisibility)
{
	ArrowActor->SetVisibility(bNewVisibility);
}



