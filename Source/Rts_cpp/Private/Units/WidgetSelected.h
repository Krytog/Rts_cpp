// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetSelected.generated.h"

/**
 * 
 */
UCLASS()
class UWidgetSelected : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UImage* IconSelected;

	UPROPERTY()
	AActor* Unit = nullptr;

public:
	void BindToUnit(AActor* UnitToBind);
	AActor* GetBindedUnit() const;

	void SetIconImage(class UTexture2D* Image);
};
