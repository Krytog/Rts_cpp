// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Misc/Optional.h"
#include "TargetSettable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetSettable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ITargetSettable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetTargetLocation(const FVector& Location) = 0;
	virtual void SetTarget(AActor* Target) = 0;
	virtual TOptional<FVector> GetTargetLocation() const = 0;
	virtual void ResetTarget() = 0;
};
