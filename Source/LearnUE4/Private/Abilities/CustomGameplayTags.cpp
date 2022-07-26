// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CustomGameplayTags.h"

#include "GameplayTagsManager.h"

const FCustomGameplayTags& FCustomGameplayTags::Get()
{
	static FCustomGameplayTags Singleton;
	return Singleton;
}

void FCustomGameplayTags::AddTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	
	UpdateInteractableTargetDataEvent = Manager.AddNativeGameplayTag(FName("GameplayEvent.UpdateInteractableTargetData"));
	InteractionHandleAbility = Manager.AddNativeGameplayTag(FName("Ability.InteractionHandle"));
	InteractionNotifyAbility = Manager.AddNativeGameplayTag(FName("Ability.InteractionNotify"));
	InteractingState = Manager.AddNativeGameplayTag(FName("State.Interacting"));
}
