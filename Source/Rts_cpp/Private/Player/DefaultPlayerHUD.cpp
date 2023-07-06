// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DefaultPlayerHUD.h"
#include "Interfaces/Selectable.h"
#include "Player/DefaultPlayer.h"
#include "EngineUtils.h"

void ADefaultPlayerHUD::SelectionBegin()
{
	GetOwningPlayerController()->GetMousePosition(StartPosition.X, StartPosition.Y);
	bSelecting = true;
}

void ADefaultPlayerHUD::SelectionUpdate()
{
	DrawRect(Color, StartPosition.X, StartPosition.Y, CurrentPosition.X - StartPosition.X, CurrentPosition.Y - StartPosition.Y);
	GetOwningPlayerController()->GetMousePosition(CurrentPosition.X, CurrentPosition.Y);
	TArray<AActor*> AllObjectsInRect;
	GetActorsInSelectionRectangle(StartPosition, CurrentPosition, AllObjectsInRect, false, false);
	TArray<ISelectable*> SelectableObjects;
	for (auto* const Object : AllObjectsInRect)
	{
		if (ISelectable* Selectable = Cast<ISelectable>(Object))
		{
			SelectableObjects.Add(Selectable);
		}
	}
	ADefaultPlayer* Player = Cast<ADefaultPlayer>(GetOwningPawn());
	Player->UpdateSelectedObjects(SelectableObjects);
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
	if (bSelecting) {
		GetOwningPlayerController()->GetMousePosition(CurrentPosition.X, CurrentPosition.Y);
	}
}