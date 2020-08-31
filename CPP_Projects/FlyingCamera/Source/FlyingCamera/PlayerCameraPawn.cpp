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
	BaseMovementSpeed = 10.f;
	SpeedMultiplier = 1.f;

	BaseRotateSpeed = 5.f;
	MinRotateYValue = -80.f;
	MaxRotateYValue = -10.f;

	BaseZoomSpeed = 50.f;
	MinZoomValue = 200.f;
	MaxZoomValue = 1500.f;

	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

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
	PlayerInputComponent->BindAxis("Zoom", this, &APlayerCameraPawn::Zoom);

}

void APlayerCameraPawn::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		float MovementSpeed = Value * BaseMovementSpeed * SpeedMultiplier;

		FVector ControllerForwardVector = GetCameraForwardDirection(false);
		FVector NewActorLocation = GetActorLocation() + (ControllerForwardVector * MovementSpeed);

		SetActorLocation(NewActorLocation);
	}
}

void APlayerCameraPawn::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		float MovementSpeed = Value * BaseMovementSpeed * SpeedMultiplier;

		FVector ControllerForwardVector = GetCameraForwardDirection(true);
		FVector NewActorLocation = GetActorLocation() + (ControllerForwardVector * MovementSpeed);

		SetActorLocation(NewActorLocation);
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
		float ZoomDelta = BaseZoomSpeed * Value * SpeedMultiplier;
		float NewZoomValue = FMath::Clamp(ZoomDelta + SpringArmComponent->TargetArmLength, MinZoomValue, MaxZoomValue);

		SpringArmComponent->TargetArmLength = NewZoomValue;
		
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

FVector APlayerCameraPawn::GetCameraForwardDirection(bool bShouldRotate)
{
	FRotator ControllerRotation = GetControlRotation();

	float ControllerYawRotation = ControllerRotation.Yaw;

	if (bShouldRotate)
	{
		// Add 90 degrees to produce the right/left movement
		ControllerYawRotation += 90.f;
	}

	FVector ControllerDirectionVector = FRotator(0.f, ControllerYawRotation, 0.f).Vector();

	float ControllerX = ControllerDirectionVector.X;
	float ControllerY = ControllerDirectionVector.Y;

	return FVector(ControllerX, ControllerY, 0.f);
}