// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CustomAbilitySystemGlobals.h"

void UCustomAbilitySystemGlobals::InitGlobalData()
{
	Super::InitGlobalData();
}

UCustomAbilitySystemGlobals& UCustomAbilitySystemGlobals::Get()
{
	UCustomAbilitySystemGlobals* Singleton = Cast<UCustomAbilitySystemGlobals>(
		IGameplayAbilitiesModule::Get().GetAbilitySystemGlobals());
	return *Singleton;
}
