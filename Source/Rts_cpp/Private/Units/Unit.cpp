// Krytog, 2023


#include "Units/Unit.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Blueprint/UserWidget.h"
#include "Player/DefaultPlayer.h"
#include "Units/WidgetSelected.h"

AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AUnit::Select()
{

}

void AUnit::Deselect()
{

}

bool AUnit::IsSelected() const
{
	return false;
}

int32 AUnit::GetTeamId() const
{
	return TeamId;
}

bool AUnit::IsInTeamWithId(int32 TeamIdToCheck) const
{
	return TeamId == TeamIdToCheck;
}

void AUnit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (WidgetSelected)
	{
		WidgetSelected->RemoveFromParentNotified(); // So parent widget will handle it 
		WidgetSelected->BindToUnit(nullptr); // Invalidate reference to this unit
		WidgetSelected = nullptr; // So GC will destroy it
	}
	NotifyThatDestroyed();
}

void AUnit::BeginPlay()
{
	Super::BeginPlay();
	if (WidgetSelectedClass)
	{
		WidgetSelected = CreateWidget<UWidgetSelected>(GetWorld()->GetFirstPlayerController(), WidgetSelectedClass);
		check(WidgetSelected);
		WidgetSelected->SetIconImage(IconSelected);
		WidgetSelected->BindToUnit(this);
	}
}

void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UWidgetSelected* AUnit::GetWidgetSelected() const
{
	return WidgetSelected;
}

FText AUnit::GetInfoName() const
{
	return {};
}

void AUnit::SetTeamId(int32 NewTeamId)
{
	TeamId = NewTeamId;
}

