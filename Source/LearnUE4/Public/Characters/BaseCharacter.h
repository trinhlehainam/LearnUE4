// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChange, float, Data);

/**
 * @brief Base class use both for Player and NPCS. \n
 * This class requires PlayerState to be instanced, and PlayerStateClass is child of ABaseCharacterState class
 *
 */
UCLASS()
class LEARNUE4_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChange OnHealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChange OnMaxHealthChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChange OnManaChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChange OnMaxManaChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChange OnStaminaChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChange OnMaxStaminaChange;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeValueChange OnWalkSpeedChange;	

	float GetHealth() const;
	float GetMaxHealth() const;
	float GetMana() const;
	float GetMaxMana() const;
	float GetStamina() const;
	float GetMaxStamina() const;
	float GetWalkSpeed() const;

	// TODO: This is hardcoded to able to updated Interactable Target Data from GA_InteractionNotify and GA_InteractionHandle get updated TargetData
	void SetInteractableTargetDataHandle(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	FGameplayAbilityTargetDataHandle GetInteractableTargetDataHandle() const;
	//

	bool IsSprinting() const;
	bool CanSprint() const;
	void Sprint();
	void StopSprinting();
protected:
	//~ Begin ACharacter Interface.

	// Called to bind functionality to input
	// Because this is base character class for both Player and NPCS, we let this method empty here
	// Override this method when our derived class use for Player
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	//~ End ACharacter Interface

	void InitializeAttributes();
	void GiveDefaultAbilities();

	void SetHealth(float Value);
	void SetMaxHealth(float Value);
	void SetMana(float Value);
	void SetMaxMana(float Value);
	void SetStamina(float Value);
	void SetMaxStamina(float Value);
	void SetWalkSpeed(float Value);

	void OnHealthAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnMaxHealthAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnManaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnMaxManaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnStaminaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnMaxStaminaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnWalkSpeedAttributeValueChange(const FOnAttributeChangeData& Data);
	
	TWeakObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = "Custom | Gameplay Ability")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultGameplayEffects;

	UPROPERTY(EditAnywhere, Category = "Custom | Gameplay Ability")
	TArray<TSubclassOf<class UBaseGameplayAbility>> DefaultAbilities;

	// TODO: Find a wait to not depend on Character
	// This is hardcoded to able to updated Interactable Target Data from GA_InteractionNotify and GA_InteractionHandle get updated TargetData
	FGameplayAbilityTargetDataHandle InteractableTargetDataHandle;

	int8 bIsSprinting:1;
};


