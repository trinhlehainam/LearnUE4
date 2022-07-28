// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

// Need to be used in game's project for Engine able to show these Gameplay Tags in Editor
struct LEARNUE4_API FCustomGameplayTags : FGameplayTagNativeAdder
{
	FGameplayTag GameplayEvent_UpdateInteractableTargetData;
	FGameplayTag Ability_InteractionHandle;
	FGameplayTag Ability_InteractionNotify;
	FGameplayTag State_Interacting;
	
	FGameplayTag InputTag_TogglePauseMenu;
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Look;
	FGameplayTag InputTag_LightAttack;

	static const FCustomGameplayTags& Get();
protected:
	virtual void AddTags() override;
};
