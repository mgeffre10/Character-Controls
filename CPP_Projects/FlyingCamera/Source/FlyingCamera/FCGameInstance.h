// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FLYINGCAMERA_API UFCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, TArray<FString>> Levels;

	void PrintLevels();

protected:

	virtual void Init() override;
};
