// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Common/AbilityInputID.h"
#include "MyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UMyGameplayAbility();
	
	// Activated immediately when granted
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;
};
