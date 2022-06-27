// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState_Player.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API APlayerState_Player : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	APlayerState_Player();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	float GetHealth() const;
	float GetMaxHealth() const;
	float GeMana() const;
	float GetMaxMana() const;
	
private:
	virtual void PostInitializeComponents() override;
	UPROPERTY()
	UAbilitySystemComponent* ASC;
};
