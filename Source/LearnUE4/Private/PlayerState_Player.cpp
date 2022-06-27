// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState_Player.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet_BaseAttributes.h"


APlayerState_Player::APlayerState_Player()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(FName("ASC"));
}

UAbilitySystemComponent* APlayerState_Player::GetAbilitySystemComponent() const
{
	return ASC;
}

float APlayerState_Player::GetHealth() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetHealthAttribute());
}

float APlayerState_Player::GetMaxHealth() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxHealthAttribute());
}

float APlayerState_Player::GeMana() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetManaAttribute());
}

float APlayerState_Player::GetMaxMana() const
{
	if (!ASC)
		return 0.f;
	return ASC->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxManaAttribute());
}

void APlayerState_Player::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ASC)
		ASC->AddSet<UAttributeSet_BaseAttributes>();
}
