// Krytog, 2023


#include "Units/Unit.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Blueprint/UserWidget.h"
#include "Player/DefaultPlayer.h"
#include "Units/WidgetSelected.h"
#include "Units/WidgetMinimap.h"
#include "Player/MinimapWidget.h"
#include "Player/PlayerUIWidget.h"

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
	DeleteWidgeSelected();
	DeleteWidgetMinimap();
}

FActorEndPlaySignature& AUnit::OnEndPlayEvent()
{
	return OnEndPlay;
}

void AUnit::BeginPlay()
{
	Super::BeginPlay();
	InitWidgetSelected();
	InitWidgetMinimap();
}

void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UWidgetSelected* AUnit::GetWidgetSelected() const
{
	return WidgetSelected;
}

void AUnit::RegisterAtMinimap(ADefaultPlayer* Player) const
{
	UPlayerUIWidget* UIWidget = Player->GetUIWidget();
	UMinimapWidget* Minimap = UIWidget->GetMinimap();
	Minimap->AddDynamicObject(this);
}

FVector2D AUnit::GetObjectCoordinates() const
{
	FVector ObjectLocation = GetActorLocation();
	return {ObjectLocation.X, ObjectLocation.Y};
}

UWidgetMinimap* AUnit::GetWidgetMinimap() const
{
	return WidgetMinimap;
}

FText AUnit::GetInfoName() const
{
	return InfoName;
}

int32 AUnit::GetPriority() const
{
	return SelectionPriority;
}

void AUnit::SetTeamId(int32 NewTeamId)
{
	TeamId = NewTeamId;
}

void AUnit::InitWidgetMinimap()
{
	if (WidgetMinimapClass)
	{
		WidgetMinimap = CreateWidget<UWidgetMinimap>(GetWorld()->GetFirstPlayerController(), WidgetMinimapClass);
		check(WidgetMinimap);
		WidgetMinimap->SetImage(IconMinimap);
		WidgetMinimap->SetColor(FLinearColor::Green);
		WidgetMinimap->SetSize(IconMinimapSize);
	}
}

void AUnit::InitWidgetSelected()
{
	if (WidgetSelectedClass)
	{
		WidgetSelected = CreateWidget<UWidgetSelected>(GetWorld()->GetFirstPlayerController(), WidgetSelectedClass);
		check(WidgetSelected);
		WidgetSelected->SetIconImage(IconSelected);
		WidgetSelected->BindToUnit(this);
	}
}

void AUnit::DeleteWidgetMinimap()
{
	if (WidgetMinimap)
	{
		WidgetMinimap->RemoveFromParent();
		WidgetMinimap = nullptr; // So GC will destroy it
	}
}

void AUnit::DeleteWidgeSelected()
{
	if (WidgetSelected)
	{
		WidgetSelected->RemoveFromParentNotified(); // So parent widget will handle it 
		WidgetSelected->BindToUnit(nullptr); // Invalidate reference to this unit
		WidgetSelected = nullptr; // So GC will destroy it
	}
}

uint32 GetTypeHash(const AUnit* Unit)
{
	return GetTypeHash(Cast<AActor>(Unit));
}
