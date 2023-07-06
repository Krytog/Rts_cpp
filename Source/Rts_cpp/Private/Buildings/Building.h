// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Building.generated.h"

UCLASS()
class RTS_CPP_API ABuilding : public AActor, public ISelectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void OnSelect() override;
	virtual void OnDeselect() override;

	bool IsSelected() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasicBuildingSettings|Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasicBuildingSettings|Mesh")
	class UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BasicBuildingSettings|SelectionDecal")
	class UStaticMeshComponent* SelectionDecalComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasicBuildingSettings|SelectionDecal")
	class UStaticMesh* SelectionDecal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasicBuildingSettings|SelectionDecal")
	class UMaterialInterface* DecalMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasicBuildingSettings|SelectionDecal")
	bool bSelected = false;
};