// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_CharacterSprint.h"

#include "Abilities/Tasks/AbilityTask_WaitAttributeChange.h"
#include "AbilitySystemComponent.h"

#include "Characters/BaseCharacter.h"

UGA_CharacterSprint::UGA_CharacterSprint()
{
}

bool UGA_CharacterSprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayTagContainer* SourceTags,
                                             const FGameplayTagContainer* TargetTags,
                                             FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ABaseCharacter* Character = Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get());

	return IsValid(Character) && Character->CanSprint();
}

void UGA_CharacterSprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	if (ABaseCharacter* Character = Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get()))
	{
		Character->Sprint();
		Character->OnStaminaChange.AddDynamic(this, &UGA_CharacterSprint::OnStaminaAttributeValueChange);
	}

	if (SprintGameplayEffectClass)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(SprintGameplayEffectClass, 1.f);
		// Cache this to remove at EndAbility. Prevent to this effect cost forever
		SprintEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, EffectSpecHandle);
	}
}

void UGA_CharacterSprint::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo,
                                     bool bReplicateEndAbility, bool bWasCancelled)
{
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get()))
	{
		Character->StopSprinting();
		Character->OnStaminaChange.RemoveDynamic(this, &UGA_CharacterSprint::OnStaminaAttributeValueChange);
	}
	
	if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
	{
		ASC->RemoveActiveGameplayEffect(CostEffectHandle);
		ASC->RemoveActiveGameplayEffect(SprintEffectHandle);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_CharacterSprint::CommitExecute(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo)
{
	ApplyCooldown(Handle, ActorInfo, ActivationInfo);

	UGameplayEffect* CostGE = GetCostGameplayEffect();
	if (CostGE)
	{
		// Cache this to remove at EndAbility. Prevent to this effect cost forever
		CostEffectHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, CostGE,
		                                              GetAbilityLevel(Handle, ActorInfo));
	}
}

void UGA_CharacterSprint::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo)
{
	CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

void UGA_CharacterSprint::OnStaminaAttributeValueChange(float NewValue)
{
	if (NewValue <= 0.f)
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}