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

float ABaseCharacterState::GetCurrentHealth() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute());
}

float ABaseCharacterState::GetBaseHealth() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetHealthAttribute());
}

float ABaseCharacterState::GetCurrentMaxHealth() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute());
}

float ABaseCharacterState::GetBaseMaxHealth() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetMaxHealthAttribute());
}

float ABaseCharacterState::GetCurrentMana() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetManaAttribute());
}

float ABaseCharacterState::GetBaseMana() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetManaAttribute());
}

float ABaseCharacterState::GetCurrentMaxMana() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxManaAttribute());
}

float ABaseCharacterState::GetBaseMaxMana() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetMaxManaAttribute());
}

float ABaseCharacterState::GetCurrentStamina() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetStaminaAttribute());
}

float ABaseCharacterState::GetBaseStamina() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetStaminaAttribute());
}

float ABaseCharacterState::GetCurrentMaxStamina() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxStaminaAttribute());
}

float ABaseCharacterState::GetBaseMaxStamina() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetMaxStaminaAttribute());
}

float ABaseCharacterState::GetCurrentWalkSpeed() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetWalkSpeedAttribute());
}

float ABaseCharacterState::GetBaseWalkSpeed() const
{
	if (!IsValid(ASC))
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetWalkSpeedAttribute());
}

void ABaseCharacterState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!IsValid(ASC)) return;
	
	ASC->AddSet<UBaseAttributeSet>();

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).AddUObject(
		this, &ABaseCharacterState::OnHealthAttributeValueChange);

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxHealthAttribute()).AddUObject(
		this, &ABaseCharacterState::OnMaxHealthAttributeValueChange);

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetManaAttribute()).AddUObject(
		this, &ABaseCharacterState::OnManaAttributeValueChange);

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxManaAttribute()).AddUObject(
		this, &ABaseCharacterState::OnMaxManaAttributeValueChange);

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaminaAttribute()).AddUObject(
		this, &ABaseCharacterState::OnStaminaAttributeValueChange);

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxStaminaAttribute()).AddUObject(
		this, &ABaseCharacterState::OnMaxStaminaAttributeValueChange);

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetWalkSpeedAttribute()).AddUObject(
		this, &ABaseCharacterState::OnWalkSpeedAttributeValueChange);
}

void ABaseCharacterState::OnHealthAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void ABaseCharacterState::OnMaxHealthAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}

void ABaseCharacterState::OnManaAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnManaChange.Broadcast(Data.NewValue);
}

void ABaseCharacterState::OnMaxManaAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnMaxManaChange.Broadcast(Data.NewValue);
}

void ABaseCharacterState::OnStaminaAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnStaminaChange.Broadcast(Data.NewValue);
}

void ABaseCharacterState::OnMaxStaminaAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnMaxStaminaChange.Broadcast(Data.NewValue);
}

void ABaseCharacterState::OnWalkSpeedAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnWalkSpeedChange.Broadcast(Data.NewValue);
}
