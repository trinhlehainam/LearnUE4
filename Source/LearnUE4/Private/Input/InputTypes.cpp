// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputTypes.h"

const UInputAction* UInputConfig::FindInputActionByGameplayTag(const FGameplayTag& InputTag) const
{
	for (const FGameplayTagInputAction& TagInput : TagInputs)
		if (TagInput.InputAction && TagInput.InputTag == InputTag)
			return TagInput.InputAction;
	
	return nullptr;
}
