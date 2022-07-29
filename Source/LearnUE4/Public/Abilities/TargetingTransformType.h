// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Type of Source Object's Transform used to perform trace or targeting
 */
UENUM(BlueprintType)
enum class EGameplayAbilityTargetingTransformType: uint8
{
	ActorTransform			UMETA(DisplayName = "Actor Transform"),
	
	// Only support using socket of Skeleton Mesh Component in ACharacter for now
	MeshSocketTransform		UMETA(Displayname = "Mesh's Socket Transform")
};
