// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Buildings/Building.h"
#include "LogisticBuilding.generated.h"

/**
 * 
 */
UCLASS()
class ALogisticBuilding : public ABuilding
{
	GENERATED_BODY()
public:
	ALogisticBuilding();

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Select() override;
	virtual void Deselect() override;

	virtual float GetLogistickRadius() const override;
	virtual void SetLogisticFieldVisibility(bool bNewVisibility);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Logistic Field")
	class UStaticMeshComponent* LogisticFieldComponent;

	// Works correctly assuming LogisticFieldMesh has radius 50 at unit scale
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Logistic Field")
	float LogisticFieldRadius = 100.0f;
};
