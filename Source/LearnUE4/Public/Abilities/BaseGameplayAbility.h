// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/AbilityInputID.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UBaseGameplayAbility();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	EAbilityInputID AbilityInputID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	bool bActivateOnGranted;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	bool bShowDebug;

protected:
	UFUNCTION(BlueprintCallable, Category="Ability")
	void AddLooseGameplayTagsToSelf(const FGameplayTagContainer GameplayTags);
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	void RemoveLooseGameplayTagsToSelf(const FGameplayTagContainer GameplayTags);
};
