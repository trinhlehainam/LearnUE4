// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseGameplayAbility.h"
#include "GA_CharacterSprint.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGA_CharacterSprint : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterSprint();

protected:
	// ~ Begin UGameplayAbility Interface

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                                const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	                                FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
	virtual void CommitExecute(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                           const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                           const FGameplayAbilityActivationInfo ActivationInfo) override;

	// ~ End UGameplayAbility Interface

	// Effect class used to modify Character Movement Speed during sprinting
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TSubclassOf<UGameplayEffect> SprintGameplayEffectClass;

	FActiveGameplayEffectHandle CostEffectHandle;
	FActiveGameplayEffectHandle SprintEffectHandle;

	UFUNCTION()
	void OnStaminaAttributeValueChange(float NewValue);
};