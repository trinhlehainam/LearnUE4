// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CustomGameplayTags.h"

#include "GameplayTagsManager.h"

namespace
{
	FCustomGameplayTags Singleton;
}

const FCustomGameplayTags& FCustomGameplayTags::Get()
{
	return Singleton;
}

void FCustomGameplayTags::AddTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	NotifyInteractionEvent = Manager.AddNativeGameplayTag(FName("GameplayEvent.NotifyInteraction"));
	InteractionHandleAbility = Manager.AddNativeGameplayTag(FName("Ability.InteractionHandle"));
	InteractionNotifyAbility = Manager.AddNativeGameplayTag(FName("Ability.InteractionNotify"));
}
