// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BaseCharacterState.generated.h"

class UCustomAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class LEARNUE4_API ABaseCharacterState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ABaseCharacterState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	float GetHealth() const;
	float GetMaxHealth() const;
	float GeMana() const;
	float GetMaxMana() const;
	
private:
	virtual void PostInitializeComponents() override;
	
	UPROPERTY()
	UCustomAbilitySystemComponent* ASC;
};