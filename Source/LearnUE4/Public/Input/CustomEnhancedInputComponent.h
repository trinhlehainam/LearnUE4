// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "InputTypes.h"
#include "Abilities/AbilityInputID.h"
#include "CustomEnhancedInputComponent.generated.h"

struct FGameplayTag;
class UInputConfig;

/**
 * 
 */
UCLASS()
class LEARNUE4_API UCustomEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass, class FuncType>
	void BindActionByInputTag(UInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);

	void BindGameplayAbilityInput(UAbilitySystemComponent* AbilitySystemComponent, int32 InputID, const UInputAction* InputAction);
};

template <class UserClass, class FuncType>
void UCustomEnhancedInputComponent::BindActionByInputTag(UInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);

	const UInputAction* InputAction = InputConfig->FindInputActionByGameplayTag(InputTag);

	check(InputAction);

	BindAction(InputAction, TriggerEvent, Object, Func);
}
