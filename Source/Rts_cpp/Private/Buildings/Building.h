// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Building.generated.h"

UENUM(BlueprintType)
enum class EPlacementMode : uint8
{
	None UMETA(DisplayName = "None"),
	AlreadyPlaced UMETA(DisplayName = "AlreadyPlaced"),
	CanBePlaced UMETA(DisplayName = "CanBePlaced"),
	CannotBePlaced UMETA(DisplayName = "CannotBePlaced")
};

UCLASS(hidecategories = ("Physics", "Cooking", "Replication", "Rendering", "WorldPartition", "HLOD"))
class RTS_CPP_API ABuilding : public AActor, public ISelectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	virtual void Select() override;
	virtual void Deselect() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	bool IsSelected() const override;
	
	virtual float GetLogistickRadius() const;

	UFUNCTION(BlueprintCallable)
	void BindToPlayer(class ADefaultPlayer* Player) const;

	UFUNCTION(BlueprintCallable)
	virtual FText GetInfoName() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetPlacementMode(EPlacementMode Mode, bool bForced = false);

	UFUNCTION(BlueprintCallable)
	virtual void Place();

	UFUNCTION(BlueprintCallable)
	EPlacementMode GetCurrentPlacementMode() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BasicBuildingSettings|Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BasicBuildingSettings|SelectionDecal")
	class UStaticMeshComponent* SelectionDecalComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BasicBuildingSettings|SelectionDecal")
	bool bSelected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BuildingSettings|BuildingNetworkAgent")
	class UBuildingNetworkAgentComponent* BuildingNetworkAgentComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BuildingSettings|BuildingInfoWidget")
	class UWidgetComponent* InfoWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Name")
	FText InfoName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BasicBuildingSettings|Placement")
	class UMaterialInterface* MaterialPlacementGood;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BasicBuildingSettings|Placement")
	class UMaterialInterface* MaterialPlacementBad;

	EPlacementMode CurrentPlacementMode = EPlacementMode::AlreadyPlaced;
};