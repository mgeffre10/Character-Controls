// Fill out your copyright notice in the Description page of Project Settings.


#include "Cover.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACover::ACover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CoverOrigin = CreateDefaultSubobject<UBoxComponent>(TEXT("CoverOrigin"));

	RootComponent = CoverOrigin;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

