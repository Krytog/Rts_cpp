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

	/* Sets texture that will be render as the minimap icon */
	void SetImage(class UTexture2D* Texture);

	/* Sets color for the minimap icon, used to differ allies, enemies and nethurals */
	void SetColor(FLinearColor Color);

	/* Updates size of the minimap icon. This size is returned from GetSize and used in actual size settings in a canvas slot */
	void UpdateSize(FVector2D NewSize);

	/* Returns size of this minimap icon. It's should be used to update size in a canvas slot */
	FVector2D GetSize() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Image;

	FVector2D Size;
};
