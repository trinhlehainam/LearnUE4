// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayEffect.h"
#include "BaseGameplayEffect.generated.h"

/**
 * Base Gameplay Effect class designed to config value in C++
 */
UCLASS(Abstract, NotBlueprintable)
class LEARNUE4_API UBaseGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
	
public:
	UBaseGameplayEffect();

protected:
	// Override this to initialize Gameplay Effect properties (Tags, Modifiers, etc)
	virtual void InitProperties() {}
	
private:
	// ~ Begin UGameplayEffect Interface
	// 
	// UGameplayEffect Reset all Tags In Here 
	// We override this to initialize tags after all tags is reset
	// Don't override this method in further subclass
	virtual void PostInitProperties() override;
	// ~ Begin UGameplayEffect Interface
};
