// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DefaultPlayer.generated.h"

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

	// Objects selection section

	void InitHUDPointer();
	void SelectionBegin();
	void SelectionFinished();

	void SelectionMergeBegin();
	void SelectionMergeFinished();
	bool bMerging = false;

	UPROPERTY()
	class ADefaultPlayerHUD* HUD;

	UPROPERTY()
	TSet<AActor*> SelectedObjects;

	TMap<AActor*, FDelegateHandle> SelectedObjectsDelegateHandlers;

	void AddObjectToSelected(AActor* Object);
	void RemoveObjectFromSelected(AActor* Object);

	void GiveTagetToSelected();

	FVector GetLocationUnderCursor() const;
public:
	// Buildings Network section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buildings Network", meta = (AllowPrivateAccess = "true"))
	class UBuildingNetworkComponent* BuildingNetwork;

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

public:
	void UpdateSelectedObjects(const TArray<AActor*>& NewSelectedObjects);
	void RemoveFromSelectedWhenDestroyed(const AActor* Object);
};