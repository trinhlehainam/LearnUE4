// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class LEARNUE4_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetMana() const;
	float GetMaxMana() const;
	
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void InitializeAttributes();
	void GiveDefaultAbilities();

	void SetHealth(float Value);
	void SetMaxHealth(float Value);
	void SetMana(float Value);
	void SetMaxMana(float Value);
	
	TWeakObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = "Custom | Gameplay Ability")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultGameplayEffects;
	
	UPROPERTY(EditAnywhere, Category = "Custom | Gameplay Ability")
	TArray<TSubclassOf<class UGameplayAbility_BaseAbility>> DefaultAbilities;
};