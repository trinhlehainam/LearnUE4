// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacterState.h"

#include "Abilities/BaseAttributeSet.h"
#include "Abilities/CustomAbilitySystemComponent.h"


ABaseCharacterState::ABaseCharacterState()
{
	ASC = CreateDefaultSubobject<UCustomAbilitySystemComponent>(FName("ASC"));
}

UAbilitySystemComponent* ABaseCharacterState::GetAbilitySystemComponent() const
{
	return ASC;
}

float ABaseCharacterState::GetHealth() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute());
}

float ABaseCharacterState::GetMaxHealth() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute());
}

float ABaseCharacterState::GeMana() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetManaAttribute());
}

float ABaseCharacterState::GetMaxMana() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxManaAttribute());
}

void ABaseCharacterState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ASC)
		ASC->AddSet<UBaseAttributeSet>();
}
