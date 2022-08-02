// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GE_AddInteractingTag.h"

#include "Abilities/CustomGameplayTags.h"

UGE_AddInteractingTag::UGE_AddInteractingTag()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	
	InheritableOwnedTagsContainer.Added.AddTag(FCustomGameplayTags::Get().State_Interacting);
}