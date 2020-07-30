// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCameraPawn.generated.h"

UCLASS()
class FLYINGCAMERA_API APlayerCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCameraPawn();

	UPROPERTY(VisibleAnywhere, Category = "Custom Attributes | Movement")
	bool bIsRotationEnabled;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float BaseMovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float BaseZoomSpeed;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float MinZoomValue;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float MaxZoomValue;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float BaseRotateSpeed;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float MinRotateYValue;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float MaxRotateYValue;

	UPROPERTY(EditAnywhere, Category = "Custom Attributes | Movement")
	float SpeedMultiplier;

	UPROPERTY(VisibleAnywhere, Category = "Custom Components")
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Custom Components")
	class UCameraComponent* CameraComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void RotateX(float Value);

	UFUNCTION()
	void RotateY(float Value);

	UFUNCTION()
	void Zoom(float Value);

	UFUNCTION()
	void EnableRotation();

	UFUNCTION()
	void DisableRotation();
};
