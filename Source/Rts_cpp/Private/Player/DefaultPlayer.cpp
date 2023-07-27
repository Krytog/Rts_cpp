// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/EngineTypes.h"
#include <cmath>
#include "Player/DefaultPlayerHUD.h"
#include "Interfaces/Selectable.h"
#include "Interfaces/TargetSettable.h"
#include "Math/UnrealMathUtility.h"
#include "Player/Components/BuildingNetworkComponent.h"
#include "Player/Components/BuildingPlacerComponent.h"
#include "Blueprint/UserWidget.h"
#include "Player/PlayerUIWidget.h"
#include "Units/WidgetSelected.h"

#define CAMERA_LAG_SPEED 2.0f

// Sets default values
ADefaultPlayer::ADefaultPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	RootComponent = SpringArm;

	SpringArm->TargetArmLength = CameraArmDistance;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = CAMERA_LAG_SPEED;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetIncludingScale, USpringArmComponent::SocketName);

	SpeedScaleCoefficient = CameraMoveSpeed / CameraArmDistance;

	BuildingNetwork = CreateDefaultSubobject<UBuildingNetworkComponent>(TEXT("BuildingNetwork"));
	BuildingPlacer = CreateDefaultSubobject<UBuildingPlacerComponent>(TEXT("BuildingPlacer"));
}

// Called when the game starts or when spawned
void ADefaultPlayer::BeginPlay()
{
	Super::BeginPlay();
	InitHUDPointer();
	InitUIWidget();
}

void ADefaultPlayer::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UIWidget->RemoveFromParent();
	UIWidget = nullptr; // So it will eventually be destroyed by GC
}

// Called every frame
void ADefaultPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCamera();
}

// Called to bind functionality to input
void ADefaultPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Wheel", this, &ADefaultPlayer::ScrollCamera);
	PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &ADefaultPlayer::LeftMouseClicked);
	PlayerInputComponent->BindAction("LeftMouse", IE_Released, this, &ADefaultPlayer::SelectionFinished);
	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &ADefaultPlayer::SelectionMergeBegin);
	PlayerInputComponent->BindAction("LeftShift", IE_Released, this, &ADefaultPlayer::SelectionMergeFinished);
	PlayerInputComponent->BindAction("RightMouse", IE_Pressed, this, &ADefaultPlayer::RightMouseClicked);
}

void ADefaultPlayer::MoveCamera()
{
	if (CursorMode == ECursorMode::Selecting) // No camera movement when selecting
	{
		return;
	}
	FVector2D MousePosition;
	const bool bOverGameWindow = GetWorld()->GetGameViewport()->GetMousePosition(MousePosition);
	if (!bOverGameWindow) {
		return;
	}
	FVector2D ViewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	const float RelativeMouseX = MousePosition.X / ViewportSize.X;
	const float RelativeMouseY = MousePosition.Y / ViewportSize.Y;
	const float CameraOffsetToAdd = GetScaledMoveSpeed() * GetWorld()->DeltaTimeSeconds;
	if (RelativeMouseX < CameraMoveOffset) 
	{
		AddActorWorldOffset(FVector(0.0f, -CameraOffsetToAdd, 0.0f));
	}
	else if (RelativeMouseX > 1.0f - CameraMoveOffset) {
		AddActorWorldOffset(FVector(0.0f, CameraOffsetToAdd, 0.0f));
	}
	if (RelativeMouseY < CameraMoveOffset)
	{
		AddActorWorldOffset(FVector(CameraOffsetToAdd, 0.0f, 0.0f));
	}
	else if (RelativeMouseY > 1.0f - CameraMoveOffset) {
		AddActorWorldOffset(FVector(-CameraOffsetToAdd, 0.0f, 0.0f));
	}
}

void ADefaultPlayer::ScrollCamera(float Value)
{
	if (!Value)
	{
		return;
	}
	Value *= -1; // Multiply it by -1 because we want to zoom in on scrolling up, in that case Value would be 1, but height must be decreased
	const float Height = GetActorLocation().Z;
	const bool bZoomIn = (Value < 0 && Height > MinCameraHeight);
	const bool bZoomOut = (Value > 0 && Height < MaxCameraHeight);
	if (bZoomIn || bZoomOut)
	{
		AddActorWorldOffset(FVector(0.0f, 0.0f, Value * CameraMoveSpeed));
	}
}

float ADefaultPlayer::GetScaledMoveSpeed() const
{
	return SpeedScaleCoefficient * std::max(GetActorLocation().Z, static_cast<double>(CameraArmDistance));
}

void ADefaultPlayer::LeftMouseClicked()
{
	switch (CursorMode)
	{
		case ECursorMode::None:
		{
			SelectionBegin();
			break;
		}
		case ECursorMode::Selecting:
		{
			// we can't get here
			break;
		}
		case ECursorMode::PlacingBuilding:
		{
			TryPlaceBuilding();
			break;
		}
		default:
		{
			break;
		}
	}
}

void ADefaultPlayer::RightMouseClicked()
{
	switch (CursorMode)
	{
		case ECursorMode::None:
		{
			GiveTagetToSelected();
			break;
		}
		case ECursorMode::Selecting:
		{
			// we can't get here
			break;
		}
		case ECursorMode::PlacingBuilding:
		{
			CancelPlacingBuilding();
			break;
		}
		default:
		{
			break;
		}
	}
}

void ADefaultPlayer::InitHUDPointer()
{
	APlayerController* MyController = Cast<APlayerController>(GetController());
	HUD = Cast<ADefaultPlayerHUD>(MyController->GetHUD());
	check(HUD);
}

void ADefaultPlayer::SelectionBegin()
{
	if (CursorMode != ECursorMode::None)
	{
		return;
	}
	CursorMode = ECursorMode::Selecting;
	HUD->SelectionBegin();
}

void ADefaultPlayer::SelectionFinished()
{
	if (CursorMode != ECursorMode::Selecting)
	{
		return;
	}
	CursorMode = ECursorMode::None;
	HUD->SelectionFinished();
}

void ADefaultPlayer::SelectionMergeBegin()
{
	bMerging = true;
}

void ADefaultPlayer::SelectionMergeFinished()
{
	bMerging = false;
}

void ADefaultPlayer::ForceEnableSelectionVisibilityOfSelected(bool bNewVisibility) const
{
	if (bNewVisibility)
	{
		for (auto* Object : SelectedObjects)
		{
			if (ISelectable* Selectable = Cast<ISelectable>(Object))
			{
				Selectable->Select();
			}
		}
	}
	else
	{
		for (auto* Object : SelectedObjects)
		{
			if (ISelectable* Selectable = Cast<ISelectable>(Object))
			{
				Selectable->Deselect();
			}
		}
	}
}

void ADefaultPlayer::AddObjectToSelected(AActor* Object)
{
	ISelectable* Selectable = Cast<ISelectable>(Object);
	if (!Selectable)
	{
		return;
	}
	if (!Selectable->IsSelected())
	{
		Selectable->Select();
	}
	FDelegateHandle DelegateHandle = Selectable->OnDestroyed().AddUObject(this, &ADefaultPlayer::RemoveFromSelectedWhenDestroyed);
	SelectedObjects.Add(Object);
	SelectedObjectsDelegateHandlers.Add(Object, DelegateHandle);
	UIWidget->AddSelectedUnitWidget(Selectable->GetWidgetSelected());
}

void ADefaultPlayer::RemoveObjectFromSelected(AActor* Object)
{
	ISelectable* Selectable = Cast<ISelectable>(Object);
	if (!Selectable)
	{
		return;
	}
	FDelegateHandle DelegateHandle;
	SelectedObjects.Remove(Object);
	SelectedObjectsDelegateHandlers.RemoveAndCopyValue(Object, DelegateHandle);
	if (Selectable->IsSelected())
	{
		Selectable->Deselect();
	}
	Selectable->OnDestroyed().Remove(DelegateHandle);
	Selectable->GetWidgetSelected()->RemoveFromParent();
}

void ADefaultPlayer::RemoveFromSelectedWhenDestroyed(const AActor* Object)
{
	SelectedObjects.Remove(Object);
	SelectedObjectsDelegateHandlers.Remove(Object);
}

UBuildingNetworkComponent* ADefaultPlayer::GetBuildingNetwork()
{
	return BuildingNetwork;
}

void ADefaultPlayer::UpdateSelectedObjects(const TArray<AActor*>& NewSelectedObjects)
{
	if (!bMerging)
	{
		TSet<AActor*> AlreadyInSet;
		for (auto* const Object : NewSelectedObjects)
		{
			if (SelectedObjects.Contains(Object))
			{
				AlreadyInSet.Add(Object);
			}
		}
		for (auto* const Object : SelectedObjects)
		{
			if (!AlreadyInSet.Contains(Object))
			{
				RemoveObjectFromSelected(Object);
			}
		}
	}
	for (auto* const Object : NewSelectedObjects)
	{
		if (SelectedObjects.Contains(Object))
		{
			continue;
		}
		AddObjectToSelected(Object);
	}
}

void ADefaultPlayer::GiveTagetToSelected()
{
	if (!SelectedObjects.Num())
	{
		return;
	}
	APlayerController* MyController = Cast<APlayerController>(GetController());
	FHitResult HitResult;
	MyController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	AActor* Target = HitResult.GetActor();
	if (Cast<ISelectable>(Target))
	{
		for (auto* const Object : SelectedObjects)
		{
			if (ITargetSettable* TargetSettable = Cast<ITargetSettable>(Object))
			{
				TargetSettable->SetTarget(Target);
			}
		}
	}
	else
	{
		const FVector Location = GetLocationUnderCursor();
		for (auto* const Object : SelectedObjects)
		{
			if (ITargetSettable* TargetSettable = Cast<ITargetSettable>(Object))
			{
				TargetSettable->SetTargetLocation(Location);
			}
		}
	}
}

FVector ADefaultPlayer::GetLocationUnderCursor() const
{
	FVector EndPoint;
	FVector WorldDirection;
	APlayerController* MyController = Cast<APlayerController>(GetController());
	MyController->DeprojectMousePositionToWorld(EndPoint, WorldDirection);
	FVector BeginPoint = Camera->GetComponentLocation();
	FVector Origin = { 0.0f, 0.0f, 0.0f, };
	FVector Normal = FVector::ZAxisVector;
	return FMath::LinePlaneIntersection(BeginPoint, EndPoint, Origin, Normal);
}

void ADefaultPlayer::EnableBuildingPlacementMode(bool bEnabled) const
{
	BuildingNetwork->EnableBuildingPlacementMode(bEnabled);
	if (!bEnabled)
	{
		ForceEnableSelectionVisibilityOfSelected(true);
	}
}

void ADefaultPlayer::StartPlacingBuilding(TSubclassOf<class ABuilding> BuildingClass)
{
	if (CursorMode != ECursorMode::None)
	{
		return;
	}
	CursorMode = ECursorMode::PlacingBuilding;
	EnableBuildingPlacementMode(true);
	BuildingPlacer->StartPlacingBuilding(BuildingClass);
}

void ADefaultPlayer::CancelPlacingBuilding()
{
	if (CursorMode != ECursorMode::PlacingBuilding)
	{
		return;
	}
	CursorMode = ECursorMode::None;
	EnableBuildingPlacementMode(false);
	BuildingPlacer->CancelPlacingBuilding();
}

void ADefaultPlayer::TryPlaceBuilding()
{
	if (CursorMode != ECursorMode::PlacingBuilding)
	{
		return;
	}
	bool bWasPlaced = BuildingPlacer->TryPlaceBuilding();
	if (bWasPlaced)
	{
		CursorMode = ECursorMode::None;
		EnableBuildingPlacementMode(false);
	}
}

void ADefaultPlayer::InitUIWidget()
{
	if (UIWidgetClass && IsLocallyControlled())
	{
		UIWidget = CreateWidget<UPlayerUIWidget>(Cast<APlayerController>(GetController()), UIWidgetClass);
		UIWidget->AddToViewport();
	}
}

void ADefaultPlayer::SetTeamId(int32 NewTeamId)
{
	TeamId = NewTeamId;
}

int32 ADefaultPlayer::GetTeamId() const
{
	return TeamId;
}

