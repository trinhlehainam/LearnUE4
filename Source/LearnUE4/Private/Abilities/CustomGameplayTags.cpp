// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CustomGameplayTags.h"

#include "GameplayTagsManager.h"

namespace ECustomGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(GameplayEvent_UpdateInteractableTargetData, "GameplayEvent.UpdateInteractableTargetData")
	UE_DEFINE_GAMEPLAY_TAG(Ability_InteractionHandle, "Ability.InteractionHandle")
	UE_DEFINE_GAMEPLAY_TAG(Ability_InteractionNotify, "Ability.InteractionNotify")
	UE_DEFINE_GAMEPLAY_TAG(State_Interacting, "State.Interacting")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_TogglePauseMenu, "InputTag.TogglePauseMenu")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack, "InputTag.LightAttack")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interact, "InputTag.Interact")
}
