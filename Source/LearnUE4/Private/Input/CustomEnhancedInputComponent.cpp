// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/CustomEnhancedInputComponent.h"

void UCustomEnhancedInputComponent::BindGameplayAbilityInput(UAbilitySystemComponent* AbilitySystemComponent,
	int32 InputID, const UInputAction* InputAction)
{
	check(AbilitySystemComponent);
	check(InputAction);

	BindAction(InputAction, ETriggerEvent::Started, AbilitySystemComponent, &UAbilitySystemComponent::AbilityLocalInputPressed, InputID);
	BindAction(InputAction, ETriggerEvent::Completed, AbilitySystemComponent, &UAbilitySystemComponent::AbilityLocalInputReleased, InputID);
}
