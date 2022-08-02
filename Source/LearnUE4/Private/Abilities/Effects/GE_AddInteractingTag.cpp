// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Effects/GE_AddInteractingTag.h"

#include "Abilities/CustomGameplayTags.h"

UGE_AddInteractingTag::UGE_AddInteractingTag()
{
}

void UGE_AddInteractingTag::InitProperties()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	InheritableOwnedTagsContainer.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Interacting")));
}
