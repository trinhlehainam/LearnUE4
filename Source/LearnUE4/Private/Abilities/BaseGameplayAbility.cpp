// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/BaseGameplayAbility.h"

#include "AbilitySystemComponent.h"

UBaseGameplayAbility::UBaseGameplayAbility()
{
	AbilityInputID = EAbilityInputID::None;
	bActivateOnGranted = false;
	bShowDebug = false;
}

void UBaseGameplayAbility::AddLooseGameplayTagsToSelf(const FGameplayTagContainer GameplayTags)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	ASC->AddLooseGameplayTags(GameplayTags);
}

void UBaseGameplayAbility::RemoveLooseGameplayTagsToSelf(const FGameplayTagContainer GameplayTags)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	ASC->RemoveLooseGameplayTags(GameplayTags);
}
