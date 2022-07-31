// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

// Need to be used in game's project for Editor recognizing our Native Gameplay Tags
// Need to restart Editor after we add/remove Gameplay Tag and recompile in order for Editor recognizing our Native Gameplay Tags
// BUG: Value in static FCustomGameplayTags instance become null when recompile in Editor
struct LEARNUE4_API FCustomGameplayTags : FGameplayTagNativeAdder
{
	FCustomGameplayTags();
	
	FGameplayTag GameplayEvent_UpdateInteractableTargetData;
	FGameplayTag Ability_InteractionHandle;
	FGameplayTag Ability_InteractionNotify;
	FGameplayTag State_Interacting;

	FGameplayTag InputTag_TogglePauseMenu;
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Look;
	FGameplayTag InputTag_LightAttack;
	FGameplayTag InputTag_Interact;

	static const FCustomGameplayTags& Get();
protected:
	virtual void AddTags() override;
};
