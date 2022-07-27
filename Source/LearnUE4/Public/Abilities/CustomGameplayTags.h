// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

// Need to be used in game's project for Engine able to show these Gameplay Tags in Editor
struct LEARNUE4_API FCustomGameplayTags : FGameplayTagNativeAdder
{
	FGameplayTag UpdateInteractableTargetDataEvent;
	FGameplayTag InteractionHandleAbility;
	FGameplayTag InteractionNotifyAbility;
	FGameplayTag InteractingState;

	static const FCustomGameplayTags& Get();
protected:
	virtual void AddTags() override;
};
