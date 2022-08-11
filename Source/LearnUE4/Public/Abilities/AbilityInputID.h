// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None			UMETA(DisplayName="None, Input ID 0"),
	Confirm			UMETA(DisplayName="Comfirm, Input ID 1"),
	Cancel			UMETA(DisplayName="Cancel, Input ID 2"),			
	Jump			UMETA(DisplayName="Jump, Input ID 3"),
	Sprint			UMETA(DisplayName="Sprint, Input ID 4"),
	Roll			UMETA(DisplayName="Roll, Input ID 5"),
	Dash			UMETA(DisplayName="Dash, Input ID 6"),
	Attack			UMETA(DisplayName="Attack, Input ID 7"),
	Interact		UMETA(DisplayName="Interact, Input ID 8")
};
