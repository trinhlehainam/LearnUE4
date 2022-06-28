// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/AttributeSet_BaseAttributes.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return ASC.Get();
}

float ABaseCharacter::GetHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetHealthAttribute());
}

float ABaseCharacter::GetMaxHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxHealthAttribute());
}

float ABaseCharacter::GetMana() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetManaAttribute());
}

float ABaseCharacter::GeManaHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxManaAttribute());
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// No binding by default because this base class for both Player and AICharacter
}

