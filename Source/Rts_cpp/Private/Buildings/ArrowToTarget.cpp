// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/ArrowToTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AArrowToTarget::AArrowToTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Root"));

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	PointerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointerMesh"));
	PointerMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void AArrowToTarget::BeginPlay()
{
	Super::BeginPlay();
}

void AArrowToTarget::InitLength()
{
	BodyLength = 2 * BodyMeshComponent->Bounds.BoxExtent.X;
	PointerLength = 2 * PointerMeshComponent->Bounds.BoxExtent.X;
}

void AArrowToTarget::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	BodyMeshComponent->SetStaticMesh(BodyMesh);
	PointerMeshComponent->SetStaticMesh(PointerMesh);
	BodyMeshComponent->SetMaterial(0, Material);
	PointerMeshComponent->SetMaterial(0, Material);
}

void AArrowToTarget::MakePointingTo(const FVector& From, const FVector& To)
{
	SetActorRotation(FRotator());
	InitLength();
	const FVector Direction = To - From;
	const float Distance = Direction.Length();
	const float ScaleFactor = (Distance - PointerLength) / BodyLength;
	BodyMeshComponent->SetWorldScale3D(FVector(ScaleFactor, 1.0f, 1.0f));
	PointerMeshComponent->SetRelativeLocation(FVector(ScaleFactor * BodyLength / 2, 0.0f, 0.0f));
	SetActorRotation(Direction.Rotation());
	const FVector ArrowPosition = (From * ScaleFactor * BodyLength / 2 + To * (ScaleFactor * BodyLength / 2 + PointerLength)) / Distance;
	SetActorLocation(ArrowPosition);
}

void AArrowToTarget::SetVisibility(bool bNewVisibility)
{
	BodyMeshComponent->SetVisibility(bNewVisibility);
	PointerMeshComponent->SetVisibility(bNewVisibility);
}
