// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

// Need to be used in project to register these custom Native Gameplay Tags to Editor
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
