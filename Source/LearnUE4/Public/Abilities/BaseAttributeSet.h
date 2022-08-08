// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class LEARNUE4_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, AttackPower);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, WalkSpeed);

protected:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// ~ Begin UAttributeSet Interface
	
	// Clamp calculated value before actually applying to Attribute
	// ExecCalc and MMC modifiers can still modify NewVale later
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Clamping attribute value again after modified
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// ~ End UAttributeSet Interface
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_WalkSpeed(const FGameplayAttributeData& OldValue);

	UPROPERTY(ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	
	UPROPERTY(ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	
	UPROPERTY(ReplicatedUsing=OnRep_AttackPower)
	FGameplayAttributeData AttackPower;

	// This is self damage (damage applied to this attribute's owner) calculated by Custom Gameplay Effect Execution Calculation
	// We want to catch modified value when an Gameplay Effect applied to this owner in PostGameplayEffectExecute to calculate final damage
	UPROPERTY(ReplicatedUsing=OnRep_AttackPower)
	FGameplayAttributeData Damage;

	UPROPERTY(ReplicatedUsing=OnRep_WalkSpeed)
	FGameplayAttributeData WalkSpeed;
};
