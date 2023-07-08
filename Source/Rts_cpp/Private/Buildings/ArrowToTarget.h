// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowToTarget.generated.h"

UCLASS()
class AArrowToTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrowToTarget();

	void SetVisibility(bool bNewVisibility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ArrowSettings|Body")
	class UStaticMeshComponent* BodyMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ArrowSettings|Pointer")
	class UStaticMeshComponent* PointerMeshComponent;

private:
	float BodyLength = 1.0f;
	float PointerLength = 1.0f;

	void InitLength();

public:	
	void MakePointingTo(const FVector& From, const FVector& To);
};
