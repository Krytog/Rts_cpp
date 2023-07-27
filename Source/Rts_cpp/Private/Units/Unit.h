// Krytog, 2023

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
	AUnit();

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	virtual void Select() override;
	virtual void Deselect() override;
	virtual bool IsSelected() const override;
	virtual int32 GetTeamId() const override;
	virtual bool IsInTeamWithId(int32 TeamIdToCheck) const override;

	virtual FText GetInfoName() const override;

	virtual void SetTeamId(int32 NewTeamId);

protected:
	virtual void BeginPlay() override;

	int32 TeamId = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Icons|Selected")
	TSubclassOf<class UWidgetSelected> WidgetSelectedClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Icons|Selected")
	class UTexture2D* IconSelected;

	UPROPERTY()
	class UWidgetSelected* WidgetSelected = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;

	class UWidgetSelected* GetWidgetSelected() const override;
};
