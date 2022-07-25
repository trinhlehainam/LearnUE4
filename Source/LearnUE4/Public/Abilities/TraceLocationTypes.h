// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Type of Source Object used to trace to find target
 */
UENUM(BlueprintType)
enum class EGameplayAbilityTraceLocationType: uint8
{
	ActorTransform,
	MeshSocketTransform,
	// Use Transform of Player Controller's View Target (Normally Camera's Transform)
	PlayerControllerViewTransform
};
