// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCameraPawn::APlayerCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsRotationEnabled = false;
	BaseMovementSpeed = 600.f;
	SpeedMultiplier = 1.f;

	BaseRotateSpeed = 5.f;
	MinRotateYValue = -80.f;
	MaxRotateYValue = -10.f;

	BaseZoomSpeed = 50.f;
	MinZoomValue = 200.f;
	MaxZoomValue = 1500.f;

	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(StaticMeshComponent);
	SpringArmComponent->TargetArmLength = 1000.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FRotator ControlRotation = FRotator(-70.f, 0.f, 0.f);
	Controller->SetControlRotation(ControlRotation);
}

// Called to bind functionality to input
void APlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Actions
	PlayerInputComponent->BindAction("EnableRotation", IE_Pressed, this, &APlayerCameraPawn::EnableRotation);
	PlayerInputComponent->BindAction("EnableRotation", IE_Released, this, &APlayerCameraPawn::DisableRotation);

	// Bind Axes
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCameraPawn::MoveRight);
	PlayerInputComponent->BindAxis("RotateX", this, &APlayerCameraPawn::RotateX);
	PlayerInputComponent->BindAxis("RotateY", this, &APlayerCameraPawn::RotateY);

}

void APlayerCameraPawn::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		float MovementSpeed = Value * BaseMovementSpeed * SpeedMultiplier;
	}
}

void APlayerCameraPawn::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		float MovementSpeed = Value * BaseMovementSpeed * SpeedMultiplier;
		float NewActorLocation = GetActorLocation().Y + MovementSpeed;

		FVector ActorLocation = GetActorLocation();
		ActorLocation.Y = NewActorLocation;

		SetActorLocation(ActorLocation);
	}
}

void APlayerCameraPawn::RotateX(float Value)
{
	if (Controller && Value != 0.f && bIsRotationEnabled)
	{
		float RotateSpeed = Value * BaseRotateSpeed * SpeedMultiplier;
		float NewYawRotation = GetControlRotation().Yaw + RotateSpeed;

		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Yaw = NewYawRotation;

		Controller->SetControlRotation(ControlRotation);
	}
}

void APlayerCameraPawn::RotateY(float Value)
{
	if (Controller && Value != 0.f && bIsRotationEnabled)
	{
		float RotateSpeed = Value * BaseRotateSpeed * SpeedMultiplier;
		float NewPitchRotation = FMath::Clamp(GetControlRotation().Pitch + RotateSpeed, MinRotateYValue, MaxRotateYValue);

		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Pitch = NewPitchRotation;

		Controller->SetControlRotation(ControlRotation);
	}
}

void APlayerCameraPawn::Zoom(float Value)
{
	if (Controller && Value != 0.f)
	{

	}
}

void APlayerCameraPawn::EnableRotation()
{
	bIsRotationEnabled = true;
}

void APlayerCameraPawn::DisableRotation()
{
	bIsRotationEnabled = false;
}