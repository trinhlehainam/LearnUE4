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


protected:
	UFUNCTION(BlueprintCallable, Category="Movement")
	void DisableMovement();
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	void EnableMovement();

	UFUNCTION(BlueprintCallable, Category="Combat")
	void EnableAttackCollision();
	
	UFUNCTION(BlueprintCallable, Category="Combat")
	void DisableAttackCollision();
	
	UFUNCTION(BlueprintCallable, Category="GameplayTag", meta=(AutoCreateRefTerm="GameplayTags"))
	void AddLooseGameplayTagsToSelf(const FGameplayTagContainer& GameplayTags);
	
	UFUNCTION(BlueprintCallable, Category="GameplayTag", meta=(AutoCreateRefTerm="GameplayTags"))
	void RemoveLooseGameplayTagsToSelf(const FGameplayTagContainer& GameplayTags);
	
	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void AddGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	bool bShowDebug;

	EMovementMode LastMovementMode;
};
