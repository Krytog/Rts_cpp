// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArrowToTagetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UArrowToTagetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArrowToTagetComponent();

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetTargetLocation(const FVector& Location);

	TOptional<FVector> GetTargetLocation();

	UFUNCTION(BlueprintCallable)
	void ResetTargetLocation();

	UFUNCTION(BlueprintCallable)
	void SetArrowVisibility(bool bNewVisibility);

private:
	FVector TargetLocation;
	bool bTargetLocationSet = false;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ArrowClass")
	TSubclassOf<class AArrowToTarget> ArrowClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AArrowToTarget* ArrowActor;
};
