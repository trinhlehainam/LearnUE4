// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSet_BaseAttributes.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

void UAttributeSet_BaseAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_BaseAttributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_BaseAttributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_BaseAttributes, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_BaseAttributes, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSet_BaseAttributes, AttackPower, COND_None, REPNOTIFY_Always);
}

void UAttributeSet_BaseAttributes::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_BaseAttributes, Health, OldValue);
}

void UAttributeSet_BaseAttributes::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_BaseAttributes, MaxHealth, OldValue);
}

void UAttributeSet_BaseAttributes::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_BaseAttributes, Mana, OldValue);
}

void UAttributeSet_BaseAttributes::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_BaseAttributes, MaxMana, OldValue);
}

void UAttributeSet_BaseAttributes::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSet_BaseAttributes, AttackPower, OldValue);
}

void UAttributeSet_BaseAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	NewValue = FMath::Max(NewValue, 0.f);
}

void UAttributeSet_BaseAttributes::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxHealth());
	}
}

/*
void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp<float>(GetHealth(), 0.f, GetMaxHealth()));
	}
}
*/
