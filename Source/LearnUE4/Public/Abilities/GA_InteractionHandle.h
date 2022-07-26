// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "GA_InteractionHandle.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGA_InteractionHandle : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_InteractionHandle();
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	// Listen UpdateDataEvent Gameplay Event sent from GA_InteractionNotify
	UFUNCTION()
	void OnUpdatedTargetData(FGameplayEventData Payload);

	FGameplayAbilityTargetDataHandle TargetDataHandle;
};


