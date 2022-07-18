// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PatrolTypes.generated.h"

UENUM(BlueprintType)
enum class EPatrolMovementType : uint8
{
	None,
	Loop,
	ReverseLoop,
	BackAndForthLoop,
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct LEARNUE4_API FPatrolInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* PatrolObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WaitTime;
};
