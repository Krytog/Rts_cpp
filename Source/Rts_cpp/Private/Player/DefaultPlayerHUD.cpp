// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DefaultPlayerHUD.h"

void ADefaultPlayerHUD::SelectionBegin()
{
	GetOwningPlayerController()->GetMousePosition(StartPosition.X, StartPosition.Y);
	bSelecting = true;
}

void ADefaultPlayerHUD::SelectionUpdate()
{
	FVector2D CurrentPosition;
	GetOwningPlayerController()->GetMousePosition(CurrentPosition.X, CurrentPosition.Y);
	DrawRect(Color, StartPosition.X, StartPosition.Y, CurrentPosition.X - StartPosition.X, CurrentPosition.Y - StartPosition.Y);
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

