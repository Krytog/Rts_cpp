// Krytog, 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMinimap.generated.h"

/**
 * 
 */
UCLASS()
class UWidgetMinimap : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetImage(class UTexture2D* Texture);
	void SetColor(FLinearColor Color);
	void SetSize(FVector2D NewSize);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image;
};
