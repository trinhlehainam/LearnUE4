// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CustomGameplayTags.h"

#include "GameplayTagsManager.h"

FCustomGameplayTags::FCustomGameplayTags()
{
}

const FCustomGameplayTags& FCustomGameplayTags::Get()
{
	static FCustomGameplayTags Singleton;
	return Singleton;
}

void FCustomGameplayTags::AddTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	
	GameplayEvent_UpdateInteractableTargetData = Manager.AddNativeGameplayTag(FName("GameplayEvent.UpdateInteractableTargetData"));
	Ability_InteractionHandle = Manager.AddNativeGameplayTag(FName("Ability.InteractionHandle"));
	Ability_InteractionNotify = Manager.AddNativeGameplayTag(FName("Ability.InteractionNotify"));
	State_Interacting = Manager.AddNativeGameplayTag(FName("State.Interacting"));
	
	InputTag_TogglePauseMenu = Manager.AddNativeGameplayTag(FName("InputTag.TogglePauseMenu"));
	InputTag_Move = Manager.AddNativeGameplayTag(FName("InputTag.Move"));
	InputTag_Look = Manager.AddNativeGameplayTag(FName("InputTag.Look"));
	InputTag_Jump = Manager.AddNativeGameplayTag(FName("InputTag.Jump"));
	InputTag_LightAttack = Manager.AddNativeGameplayTag(FName("InputTag.LightAttack"));
	InputTag_Interact = Manager.AddNativeGameplayTag(FName("InputTag.Interact"));
}