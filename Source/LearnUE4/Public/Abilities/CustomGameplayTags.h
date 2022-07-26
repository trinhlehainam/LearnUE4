// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

struct LEARNUE4_API FCustomGameplayTags : FGameplayTagNativeAdder
{
	FGameplayTag NotifyInteractionEvent;
	FGameplayTag InteractionHandleAbility;
	FGameplayTag InteractionNotifyAbility;

	static const FCustomGameplayTags& Get();
protected:
	virtual void AddTags() override;
};
