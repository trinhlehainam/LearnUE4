// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BaseCharacterState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChange, float, NewValue);

class UCustomAbilitySystemComponent;
struct FOnAttributeChangeData;

/**
 * 
 */
UCLASS()
class LEARNUE4_API ABaseCharacterState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Name of the AbilitySystemComponent component. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static const FName AbilitySystemComponentName;

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

protected:
	virtual void PostInitializeComponents() override;

	void OnHealthAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnMaxHealthAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnManaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnMaxManaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnStaminaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnMaxStaminaAttributeValueChange(const FOnAttributeChangeData& Data);
	void OnWalkSpeedAttributeValueChange(const FOnAttributeChangeData& Data);

	UPROPERTY()
	UCustomAbilitySystemComponent* ASC;
};
