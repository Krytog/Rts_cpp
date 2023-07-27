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

public:
	FReply NativeOnMouseButtonDown(const FGeometry &Geometry, const FPointerEvent& MouseEvent) override;

	void BindToUnit(AActor* UnitToBind);
	AActor* GetBindedUnit() const;

	void SetIconImage(class UTexture2D* Image);

	DECLARE_EVENT_OneParam(UWidgetSelected, FEventRemovedFromParent, UWidgetSelected*)

	FEventRemovedFromParent& OnRemovedFromParent();

	void RemoveFromParentNotified();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UImage* IconSelected;

	UPROPERTY()
	AActor* Unit = nullptr;

private:
	FEventRemovedFromParent EventRemovedFromParent;
};
