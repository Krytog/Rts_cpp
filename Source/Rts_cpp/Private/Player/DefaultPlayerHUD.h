// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADefaultPlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	void SelectionBegin();
	void SelectionFinished();
	void SelectionUpdate();

	void Tick(float DeltaTime) override;

	void DrawHUD() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SelectionRectColor")
	FLinearColor Color;

private:
	FVector2D StartPosition;
	FVector2D CurrentPosition;
	bool bSelecting = false;
};
