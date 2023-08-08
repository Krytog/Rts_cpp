// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/Components/ArrowToTargetComponent.h"
#include "Interfaces/Selectable.h"
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
	ClearTargetActor();
}

void UArrowToTargetComponent::SetTarget(AActor* Target)
{
	if (Target == GetOwner())
	{
		return;
	}
	TargetActor = Target;
	bTargetSet = true;
	SetComponentTickEnabled(true);
	if (ISelectable* Selectable = Cast<ISelectable>(Target))
	{
		Selectable->OnEndPlayEvent().AddDynamic(this, &UArrowToTargetComponent::SetTargetLocationWhenTargetDestroyed);
	}
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
	ClearTargetActor();
	bTargetSet = false;
	ArrowActor->SetVisibility(false);
}

void UArrowToTargetComponent::SetTargetLocationWhenTargetDestroyed(AActor* Destroyed, EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason != EEndPlayReason::Destroyed)
	{
		return;
	}
	TargetActor = nullptr;
	SetComponentTickEnabled(false);
}

void UArrowToTargetComponent::SetArrowVisibility(bool bNewVisibility)
{
	ArrowActor->SetVisibility(bNewVisibility);
}

void UArrowToTargetComponent::ClearTargetActor()
{
	if (ISelectable* Selectable = Cast<ISelectable>(TargetActor))
	{
		Selectable->OnEndPlayEvent().RemoveDynamic(this, &UArrowToTargetComponent::SetTargetLocationWhenTargetDestroyed);
	}
	TargetActor = nullptr;
	SetComponentTickEnabled(false);
}

bool UArrowToTargetComponent::IsTargetSet() const
{
	return bTargetSet;
}

