// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/Components/ArrowToTargetComponent.h"
#include "Buildings/ArrowToTarget.h"

// Sets default values for this component's properties
UArrowToTargetComponent::UArrowToTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UArrowToTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Emerald, FString::Printf(TEXT("TICKED!")));
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!TargetActor)
	{
		SetComponentTickEnabled(false);
		return;
	}
	TargetLocation = TargetActor->GetActorLocation();
	ArrowActor->MakePointingTo(GetOwner()->GetActorLocation(), TargetLocation);
}

void UArrowToTargetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->DestroyActor(ArrowActor);
}

// Called when the game starts
void UArrowToTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	ArrowActor = GetWorld()->SpawnActor<AArrowToTarget>(ArrowClass);
	ArrowActor->SetVisibility(false);
}

void UArrowToTargetComponent::SetTargetLocation(const FVector& Location)
{
	TargetLocation = Location;
	bTargetSet = true;
	ArrowActor->MakePointingTo(GetOwner()->GetActorLocation(), Location);
	TargetActor = nullptr;
	SetComponentTickEnabled(false);
}

void UArrowToTargetComponent::SetTarget(AActor* Target)
{
	TargetActor = Target;
	bTargetSet = true;
	SetComponentTickEnabled(true);
}

TOptional<FVector> UArrowToTargetComponent::GetTargetLocation() const
{
	if (!bTargetSet)
	{
		return NullOpt;
	}
	return TargetLocation;
}

AActor* UArrowToTargetComponent::GetTargetActor() const
{
	return TargetActor;
}

void UArrowToTargetComponent::ResetTarget()
{
	bTargetSet = false;
	TargetActor = nullptr;
	ArrowActor->SetVisibility(false);
	SetComponentTickEnabled(false);
}

void UArrowToTargetComponent::SetArrowVisibility(bool bNewVisibility)
{
	ArrowActor->SetVisibility(bNewVisibility);
}

bool UArrowToTargetComponent::IsTargetSet() const
{
	return bTargetSet;
}



