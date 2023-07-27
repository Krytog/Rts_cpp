// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Selectable.h"
#include "Units/Unit.h"
#include "Building.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor=true))
enum class EPlacementFlags : uint8
{
	CanBePlaced		= 0 UMETA(DisplayName = "CanBePlaced"),
	AlreadyPlaced	= 1 << 0 UMETA(DisplayName = "AlreadyPlaced"),
	PositionBlocked	= 1 << 1 UMETA(DisplayName = "CanBePlaced"),
	NoLogistic		= 1 << 2 UMETA(DisplayName = "CannotBePlaced")
}; 
ENUM_CLASS_FLAGS(EPlacementFlags);

UCLASS(hidecategories = ("Physics", "Cooking", "Replication", "Rendering", "WorldPartition", "HLOD", "Collision", "Events", "DataLayers", "Input"))
class RTS_CPP_API ABuilding : public AUnit
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

	void AddPlacementFlag(EPlacementFlags Flag);
	void RemovePlacementFlag(EPlacementFlags Flag);

	uint8 GetPlacementFlags() const;
	bool HasPlacementFlag(EPlacementFlags Flag) const;
	bool CanBePlaced() const;

	void SetAppropriatePlacementMaterial();

	// Returns whether the building was placed
	bool TryPlace();

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

	uint8 PlacementFlags = 0;

private:
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	int32 OverlappedActors = 0;
};