// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Effects/BaseGameplayEffect.h"

UBaseGameplayEffect::UBaseGameplayEffect()
{
}

void UBaseGameplayEffect::PostInitProperties()
{
	Super::PostInitProperties();

	InitProperties();

	UpdateInheritedTagProperties();
}
