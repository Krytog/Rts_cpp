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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


	// Mouse handling section

	void MoveCamera();
	void ScrollCamera(float Value);
	
	float GetScaledMoveSpeed() const;
	float SpeedScaleCoefficient;

	ECursorMode CursorMode = ECursorMode::None;

	void LeftMouseClicked();
	void RightMouseClicked();

	// Objects selection section

	void InitHUDPointer();
	void SelectionBegin();
	void SelectionFinished();

	void SelectionMergeBegin();
	void SelectionMergeFinished();
	bool bMerging = false;

	/* Callback for OnEndPlayEvent */
	UFUNCTION()
	void RemoveFromSelectedWhenDestroyed(AActor* Object, EEndPlayReason::Type EndPlayReason);

	/* This property should be changed only if current player UI widget is supporting new number */
	int32 MaxSelectedInGroup = 36;

	/* Sometimes various events affect selection visibility of selected objects, this function manually changes their selection visibility */
	void ForceEnableSelectionVisibilityOfSelected(bool bNewVisibility) const;

	UPROPERTY()
	class ADefaultPlayerHUD* HUD;

	UPROPERTY()
	TSet<class AUnit*> SelectedObjects;

	void AddUnitToSelected(AUnit* Unit);
	void RemoveUnitFromSelected(AUnit* Unit);

	void GiveTagetToSelected();

	// Buildings section
	UPROPERTY()
	class UBuildingNetworkComponent* BuildingNetwork;

	void EnableBuildingPlacementMode(bool bEnabled) const;

	UPROPERTY()
	class UBuildingPlacerComponent* BuildingPlacer;

	// UI section

	void InitUIWidget();

	UPROPERTY()
	class UPlayerUIWidget* UIWidget;

	// Team section
	
	int32 TeamId = -1;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float CameraArmDistance = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float MinCameraHeight = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float MaxCameraHeight = 2500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float CameraMoveOffset = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CameraMovement")
	float CameraMoveSpeed = 250.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UPlayerUIWidget> UIWidgetClass;

public:
	void UpdateSelectedObjects(TArray<AUnit*>& NewSelectedObjects);

	FVector GetLocationUnderCursor() const;

	class UBuildingNetworkComponent* GetBuildingNetwork();

	UFUNCTION(BlueprintCallable)
	void StartPlacingBuilding(TSubclassOf<class ABuilding> BuildingClass);

	UFUNCTION(BlueprintCallable)
	void CancelPlacingBuilding();

	void TryPlaceBuilding();

	UFUNCTION(BlueprintCallable)
	void SetTeamId(int32 NewTeamId);

	int32 GetTeamId() const;
};