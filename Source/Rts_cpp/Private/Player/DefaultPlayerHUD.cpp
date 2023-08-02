// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DefaultPlayerHUD.h"
#include "Player/DefaultPlayer.h"
#include "EngineUtils.h"
#include "Units/Unit.h"

void ADefaultPlayerHUD::SelectionBegin()
{
	GetOwningPlayerController()->GetMousePosition(StartPosition.X, StartPosition.Y);
	bSelecting = true;
}

void ADefaultPlayerHUD::SelectionUpdate()
{
	DrawRect(Color, StartPosition.X, StartPosition.Y, CurrentPosition.X - StartPosition.X, CurrentPosition.Y - StartPosition.Y);
	GetOwningPlayerController()->GetMousePosition(CurrentPosition.X, CurrentPosition.Y);
	TArray<AUnit*> AllObjectsInRect;
	GetActorsInSelectionRectangle(StartPosition, CurrentPosition, AllObjectsInRect, false, false);
	ADefaultPlayer* Player = Cast<ADefaultPlayer>(GetOwningPawn());
	Player->UpdateSelectedObjects(AllObjectsInRect);
}

void ADefaultPlayerHUD::SelectionFinished()
{
	bSelecting = false;
}


void ADefaultPlayerHUD::DrawHUD()
{
	Super::DrawHUD();
	if (bSelecting)
	{
		SelectionUpdate();
	}
}

void ADefaultPlayerHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bSelecting) {
		GetOwningPlayerController()->GetMousePosition(CurrentPosition.X, CurrentPosition.Y);
	}
}