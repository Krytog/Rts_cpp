// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "Interfaces/TargetSettable.h"
#include "CommanderBuilding.generated.h"

/**
 * 
 */
UCLASS()
class ACommanderBuilding : public ABuilding, public ITargetSettable
{
	GENERATED_BODY()

public:
	ACommanderBuilding();

	void SetTargetLocation(const FVector& Location) override;
	void SetTarget(AActor* Target) override;
	TOptional<FVector> GetTargetLocation() const override;
	void ResetTarget() override;

	void Select() override;
	void Deselect() override;

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CommanderBuildingSettings|ArrowComponent")
	class UArrowToTargetComponent* ArrowComponent;
};
