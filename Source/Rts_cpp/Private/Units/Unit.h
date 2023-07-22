// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Unit.generated.h"

UCLASS()
class AUnit : public AActor, public ISelectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

	virtual void Select() override;
	virtual void Deselect() override;
	virtual bool IsSelected() const override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual FText GetInfoName() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
