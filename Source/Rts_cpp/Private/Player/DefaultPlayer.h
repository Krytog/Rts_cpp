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

	void OnMouseMove();
	void OnMouseScroll(float Value);
	
	float GetScaledMoveSpeed() const;
	float SpeedScaleCoefficient;

	// Objects selection section

	void InitHUDPointer();
	void OnSelectionBegin();
	void OnSelectionFinished();

	UPROPERTY()
	class ADefaultPlayerHUD* HUD;

	UPROPERTY()
	TArray<class ISelectable*> SelectedObjects;

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
	void UpdateSelectedObjects(TArray<class ISelectable*>& NewSelectedObjects);
};