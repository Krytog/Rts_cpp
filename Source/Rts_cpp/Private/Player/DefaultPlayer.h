// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DefaultPlayer.generated.h"

UENUM(BlueprintType)
enum class ECursorMode : uint8
{
	None UMETA(DisplayName = "None"),
	Selecting UMETA(DisplayName = "Selecting"),
	PlacingBuilding UMETA(DisplayName = "PlacingBuildings"),
};

UCLASS()
class RTS_CPP_API ADefaultPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADefaultPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/* A spring arm that is used for smooth camera movement */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/* The main camera through which the player sees the world */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


	// Mouse handling section

	/* Moves the camera along XY plane*/
	void MoveCamera();

	/* Changes the height of the camera */
	void ScrollCamera(float Value);
	
	/* Returns the speed for the camera at the current camera height */
	float GetScaledMoveSpeed() const;

	/* A special scale coefficient that is used for current camera speed calcualtions. Calculated once at the very begining of gameplay */
	float SpeedScaleCoefficient;

	/* The CursorMode is used to prevent the player from accidentally doing multiple actions at the same time */
	ECursorMode CursorMode = ECursorMode::None;

	/* The functionallity that should be binded to LeftMouseClick event */
	void LeftMouseClicked();

	/* The functionallity that should be binded to RightMouseClick event */
	void RightMouseClicked();

	// Objects selection section

	/* Initializes the pointer for HUD, that will be used to draw selection rectangle and find units within */
	void InitHUDPointer();

	/* This function should be called when the player starts units selection. It synchronizes all systems responsible for that */
	void SelectionBegin();
	
	/* This function should be called when the player finishes units selection. It synchronizes all systems responsible for that */
	void SelectionFinished();

	/* Changes selection mode to merging */
	void SelectionMergeBegin();

	/* Changes selection mode to normal (not merging) */
	void SelectionMergeFinished();
	
	/* Is the player currently in merging selection mode? */
	bool bMerging = false;

	/* Callback for OnEndPlayEvent. When the object is destroyed, it is deleted from SelectedObjects */
	UFUNCTION()
	void RemoveFromSelectedWhenDestroyed(AActor* Object, EEndPlayReason::Type EndPlayReason);

	/* This property should be changed only if current player UI widget is supporting new number */
	int32 MaxSelectedInGroup = 36;

	/* Sometimes various events affect selection visibility of selected objects, this function manually changes their selection visibility. */
	void ForceEnableSelectionVisibilityOfSelected(bool bNewVisibility) const;

	/* A pointer to the player's HUD */
	UPROPERTY()
	class ADefaultPlayerHUD* HUD;

	/* The objects currently selected by the player */
	UPROPERTY()
	TSet<class AUnit*> SelectedObjects;

	/* Adds a unit to SelectedObjects and does all the required synchronization work */
	void AddUnitToSelected(AUnit* Unit);

	/* Removes a unit from SelectedObjects and does all the required synchronization work */
	void RemoveUnitFromSelected(AUnit* Unit);

	/* Gives target to all objects contained in SelectedObjects */
	void GiveTagetToSelected();

	// Buildings section

	/* A component responsible for buildings network */
	UPROPERTY()
	class UBuildingNetworkComponent* BuildingNetwork;

	/* Turns on and off building placement mode */
	void EnableBuildingPlacementMode(bool bEnabled) const;

	/* A component responsible for placing buildings into the world */
	UPROPERTY()
	class UBuildingPlacerComponent* BuildingPlacer;

	// UI section

	/* Initializes the UI widget and does some basic setup */
	void InitUIWidget();

	/* A timer handle minimap update is bounded to */
	FTimerHandle MinimapUpdateTimer;

	/* A pointer to the player's UI */
	UPROPERTY()
	class UPlayerUIWidget* UIWidget;

	// Team section
	
	/* The player's TeamId */
	int32 TeamId = -1;

protected:
	/* The length of the player's camera arm */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float CameraArmDistance = 150.0f;

	/* The minimal height over the battlefield the player's camera can descend to */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float MinCameraHeight = 0.0f;

	/* The maximal height over the battlefield the player's camera can ascend to */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float MaxCameraHeight = 2500.0f;

	/* The offset from screen boarders that will cause the player's camera to move */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float CameraMoveOffset = 0.05f;

	/* The speed of the player's camera movement */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float CameraMoveSpeed = 250.0f;

	/* The blueprint class that will be used as player's UI */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UPlayerUIWidget> UIWidgetClass;

	/* The time interval between updates of the player's minimap. The lower value is, the more performance consuming the minimap is */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI|Minimap")
	float MinimapUpdateInterval = 0.1f;

public:
	/* Updates SelectedObjects, adding new ones and removing old objects (if not merging) */
	void UpdateSelectedObjects(TArray<AUnit*>& NewSelectedObjects);

	/* Returns the position in the game world under the player's cursor */
	FVector GetLocationUnderCursor() const;

	/* Returns the pointer to the player's BuildingNetwork component */
	class UBuildingNetworkComponent* GetBuildingNetwork();

	/* Starts process of placing a building */
	UFUNCTION(BlueprintCallable)
	void StartPlacingBuilding(TSubclassOf<class ABuilding> BuildingClass);

	/* Cancels process of placing a bulding */
	UFUNCTION(BlueprintCallable)
	void CancelPlacingBuilding();

	/* Tries to finish the process of placing a builidng. If successed, the process of placing stops, otherwise the process goes on */
	void TryPlaceBuilding();

	/* Sets the player's TeamId */
	UFUNCTION(BlueprintCallable)
	void SetTeamId(int32 NewTeamId);

	/* Returns the player's TeamId */
	int32 GetTeamId() const;

	/* Returns the pointer to the player's UI widget */
	class UPlayerUIWidget* GetUIWidget() const;
};