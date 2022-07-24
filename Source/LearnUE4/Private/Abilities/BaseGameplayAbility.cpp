// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/BaseGameplayAbility.h"

UBaseGameplayAbility::UBaseGameplayAbility()
{
	AbilityInputID = EAbilityInputID::None;
	bActivateOnGranted = false;
	bShowDebug = false;
}
