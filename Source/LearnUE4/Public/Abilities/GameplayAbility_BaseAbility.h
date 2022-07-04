// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LearnUE4/Common/AbilityInputID.h"
#include "GameplayAbility_BaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGameplayAbility_BaseAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGameplayAbility_BaseAbility();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;
};
