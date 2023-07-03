// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/EngineTypes.h"

#define CAMERA_LAG_SPEED 2.0f

// Sets default values
ADefaultPlayer::ADefaultPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	RootComponent = SpringArm;

	SpringArm->TargetArmLength = CameraDistance;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = CAMERA_LAG_SPEED;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetIncludingScale, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ADefaultPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

