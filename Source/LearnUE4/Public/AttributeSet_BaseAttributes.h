// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_BaseAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class LEARNUE4_API UAttributeSet_BaseAttributes : public UAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(UAttributeSet_BaseAttributes, Health);
	ATTRIBUTE_ACCESSORS(UAttributeSet_BaseAttributes, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAttributeSet_BaseAttributes, Mana);
	ATTRIBUTE_ACCESSORS(UAttributeSet_BaseAttributes, MaxMana);
	ATTRIBUTE_ACCESSORS(UAttributeSet_BaseAttributes, AttackPower);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Clamp calculated value before actually applying to Attribute
	// ExecutionCalc and MMC modifiers can still modify NewVale later
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Clamping attribute value again after modified
	// virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
private:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UPROPERTY(ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	
	UPROPERTY(ReplicatedUsing=OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
};
