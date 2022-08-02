// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseGameplayEffect.h"
#include "GE_AddInteractingTag.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGE_AddInteractingTag : public UBaseGameplayEffect
{
	GENERATED_BODY()
	
public:
	UGE_AddInteractingTag();

	virtual void InitProperties() override;
};
