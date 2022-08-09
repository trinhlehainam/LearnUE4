// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChange, float, NewValue);

class UBaseGameplayAbility;
class UCustomAbilitySystemComponent;

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

	UPROPERTY(BlueprintAssignable, Category="Atrribute")
	FOnAttributeValueChange OnHealthChange;
	UPROPERTY(BlueprintAssignable, Category="Atrribute")
	FOnAttributeValueChange OnMaxHealthChange;
	UPROPERTY(BlueprintAssignable, Category="Atrribute")
	FOnAttributeValueChange OnManaChange;
	UPROPERTY(BlueprintAssignable, Category="Atrribute")
	FOnAttributeValueChange OnMaxManaChange;
	UPROPERTY(BlueprintAssignable, Category="Atrribute")
	FOnAttributeValueChange OnStaminaChange;
	UPROPERTY(BlueprintAssignable, Category="Atrribute")
	FOnAttributeValueChange OnMaxStaminaChange;
	UPROPERTY(BlueprintAssignable, Category="Atrribute")
	FOnAttributeValueChange OnWalkSpeedChange;

	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetCurrentHealth() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetBaseHealth() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetCurrentMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetBaseMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetCurrentMana() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetBaseMana() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetCurrentMaxMana() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetBaseMaxMana() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetCurrentStamina() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetBaseStamina() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetCurrentMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetBaseMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetCurrentWalkSpeed() const;
	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetBaseWalkSpeed() const;

	// TODO: This is hardcoded to able to updated Interactable Target Data from GA_InteractionNotify and GA_InteractionHandle get updated TargetData
	void SetInteractableTargetDataHandle(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	FGameplayAbilityTargetDataHandle GetInteractableTargetDataHandle() const;
	//

	bool IsSprinting() const;
	bool CanSprint() const;
	virtual void Sprint();
	virtual void StopSprinting();
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

	void OnHealthAttributeValueChange(const FOnAttributeChangeData& NewValue);
	void OnMaxHealthAttributeValueChange(const FOnAttributeChangeData& NewValue);
	void OnManaAttributeValueChange(const FOnAttributeChangeData& NewValue);
	void OnMaxManaAttributeValueChange(const FOnAttributeChangeData& NewValue);
	void OnStaminaAttributeValueChange(const FOnAttributeChangeData& NewValue);
	void OnMaxStaminaAttributeValueChange(const FOnAttributeChangeData& NewValue);
	void OnWalkSpeedAttributeValueChange(const FOnAttributeChangeData& NewValue);

	TWeakObjectPtr<UCustomAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, Category = "Custom | Gameplay Ability")
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;

	UPROPERTY(EditAnywhere, Category = "Custom | Gameplay Ability")
	TArray<TSubclassOf<UBaseGameplayAbility>> DefaultAbilities;

	// TODO: Find a way to not depend on Character
	// This is hardcoded to able to updated Interactable Target Data from GA_InteractionNotify and GA_InteractionHandle get updated TargetData
	FGameplayAbilityTargetDataHandle InteractableTargetDataHandle;

	int8 bIsSprinting:1;
};
