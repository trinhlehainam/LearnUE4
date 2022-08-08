// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/BaseGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GameplayCueManager.h"
#include "Abilities/CustomAbilitySystemGlobals.h"

UBaseGameplayAbility::UBaseGameplayAbility()
{
	AbilityInputID = EAbilityInputID::None;
	bActivateOnGranted = false;
	bShowDebug = false;
}

void UBaseGameplayAbility::AddLooseGameplayTagsToSelf(const FGameplayTagContainer& GameplayTags)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	ASC->AddLooseGameplayTags(GameplayTags);
}

void UBaseGameplayAbility::RemoveLooseGameplayTagsToSelf(const FGameplayTagContainer& GameplayTags)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	ASC->RemoveLooseGameplayTags(GameplayTags);
}

void UBaseGameplayAbility::ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag,
	const FGameplayCueParameters& GameplayCueParameters)
{
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwningActorFromActorInfo(), GameplayCueTag, EGameplayCueEvent::Type::Executed, GameplayCueParameters);
}

void UBaseGameplayAbility::AddGameplayCueLocal(const FGameplayTag GameplayCueTag,
	const FGameplayCueParameters& GameplayCueParameters)
{
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwningActorFromActorInfo(), GameplayCueTag, EGameplayCueEvent::Type::OnActive, GameplayCueParameters);
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwningActorFromActorInfo(), GameplayCueTag, EGameplayCueEvent::Type::WhileActive, GameplayCueParameters);
}

void UBaseGameplayAbility::RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag,
	const FGameplayCueParameters& GameplayCueParameters)
{
	UCustomAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(
		GetOwningActorFromActorInfo(), GameplayCueTag, EGameplayCueEvent::Type::Removed, GameplayCueParameters);
}
