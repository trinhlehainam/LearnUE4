// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "GA_CharacterMontageJump.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGA_CharacterMontageJump : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterMontageJump();

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                                const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	                                FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Montage")
	UAnimMontage* JumpMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Montage")
	FName AnticipationSection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Montage")
	FName BeginSection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Montage")
	FName LoopSection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Montage")
	FName EndSection;
};
