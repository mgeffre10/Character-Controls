// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cover.generated.h"

UCLASS()
class MOVEMENT_API ACover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACover();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CoverOrigin;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

};
