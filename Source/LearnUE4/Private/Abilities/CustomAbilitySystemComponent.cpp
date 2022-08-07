// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CustomAbilitySystemComponent.h"

#include "Abilities/CustomAbilitySystemGlobals.h"

#include "GameplayCueManager.h"

void UCustomAbilitySystemComponent::ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag,
                                                            const FGameplayCueParameters& GameplayCueParameters)
{
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Executed, GameplayCueParameters);
}

void UCustomAbilitySystemComponent::AddGameplayCueLocal(const FGameplayTag GameplayCueTag,
                                                        const FGameplayCueParameters& GameplayCueParameters)
{
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::OnActive, GameplayCueParameters);
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::WhileActive, GameplayCueParameters);
}

void UCustomAbilitySystemComponent::RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag,
                                                           const FGameplayCueParameters& GameplayCueParameters)
{
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Removed, GameplayCueParameters);
}
