// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacterState.h"

#include "AbilitySystemComponent.h"
#include "Abilities/AttributeSet_BaseAttributes.h"


ABaseCharacterState::ABaseCharacterState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(FName("ASC"));
}

UAbilitySystemComponent* ABaseCharacterState::GetAbilitySystemComponent() const
{
	return ASC;
}

float ABaseCharacterState::GetHealth() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetHealthAttribute());
}

float ABaseCharacterState::GetMaxHealth() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxHealthAttribute());
}

float ABaseCharacterState::GeMana() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetManaAttribute());
}

float ABaseCharacterState::GetMaxMana() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxManaAttribute());
}

void ABaseCharacterState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ASC)
		ASC->AddSet<UAttributeSet_BaseAttributes>();
}
