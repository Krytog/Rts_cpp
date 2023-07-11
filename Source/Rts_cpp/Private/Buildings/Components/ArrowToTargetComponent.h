// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArrowToTargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UArrowToTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArrowToTargetComponent();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetTargetLocation(const FVector& Location);
	void SetTarget(AActor* Target);

	TOptional<FVector> GetTargetLocation() const;
	AActor* GetTargetActor() const;

	bool IsTargetSet() const;
	void ResetTarget();

	void SetArrowVisibility(bool bNewVisibility);

private:
	FVector TargetLocation;
	bool bTargetSet = false;

	UPROPERTY()
	AActor* TargetActor = nullptr;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ArrowClass")
	TSubclassOf<class AArrowToTarget> ArrowClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AArrowToTarget* ArrowActor;
};
