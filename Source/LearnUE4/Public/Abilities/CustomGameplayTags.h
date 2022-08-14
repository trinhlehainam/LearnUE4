// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

namespace ECustomGameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_UpdateInteractableTargetData)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_InteractionHandle)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_InteractionNotify)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Interacting)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Invincible)

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_TogglePauseMenu)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Interact)
}