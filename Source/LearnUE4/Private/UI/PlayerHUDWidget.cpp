// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/PlayerHUDWidget.h"

#include "Characters/BaseCharacter.h"

#include "Components/ProgressBar.h"
#include "Components/WidgetSwitcher.h"

void UPlayerHUDWidget::SwitchShowInteractUIText_Implementation(bool bIsGamepadKey)
{
	InteractUISwitcher->SetActiveWidgetIndex(!bIsGamepadKey ? 0 : 1);
}

UWidgetSwitcher* UPlayerHUDWidget::GetInteractWidget()
{
	return InteractUISwitcher;
}

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABaseCharacter* Character = GetOwningPlayerPawn<ABaseCharacter>();

	check(Character);

	Character->OnHealthChange.AddDynamic(this, &UPlayerHUDWidget::OnHealthAttributeChange);
	Character->OnMaxHealthChange.AddDynamic(this, &UPlayerHUDWidget::OnMaxHealthAttributeChange);
	Character->OnManaChange.AddDynamic(this, &UPlayerHUDWidget::OnManaAttributeChange);
	Character->OnMaxManaChange.AddDynamic(this, &UPlayerHUDWidget::OnMaxManaAttributeChange);
	Character->OnStaminaChange.AddDynamic(this, &UPlayerHUDWidget::OnStaminaAttributeChange);
	Character->OnMaxStaminaChange.AddDynamic(this, &UPlayerHUDWidget::OnMaxStaminaAttributeChange);
	
	Health = Character->GetCurrentHealth();
	MaxHealth = Character->GetCurrentMaxHealth();
	Mana = Character->GetCurrentMana();
	MaxMana = Character->GetCurrentMaxMana();
	Stamina = Character->GetCurrentStamina();
	MaxStamina = Character->GetCurrentMaxStamina();

	if (HealthBar)
		HealthBar->SetPercent(Health / MaxHealth);

	if (ManaBar)
		ManaBar->SetPercent(Mana / MaxMana);
	
	if (StaminaBar)
		StaminaBar->SetPercent(Stamina / MaxStamina);

	if (InteractUISwitcher)
		InteractUISwitcher->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHUDWidget::OnHealthAttributeChange(float NewValue)
{
	Health = NewValue;
	HealthBar->SetPercent(Health / MaxHealth);
}

void UPlayerHUDWidget::OnMaxHealthAttributeChange(float NewValue)
{
	MaxHealth = NewValue;
	HealthBar->SetPercent(Health / MaxHealth);
}

void UPlayerHUDWidget::OnManaAttributeChange(float NewValue)
{
	Mana = NewValue;
	ManaBar->SetPercent(Mana / MaxMana);
}

void UPlayerHUDWidget::OnMaxManaAttributeChange(float NewValue)
{
	MaxMana = NewValue;
	ManaBar->SetPercent(Mana / MaxMana);
}

void UPlayerHUDWidget::OnStaminaAttributeChange(float NewValue)
{
	Stamina = NewValue;
	StaminaBar->SetPercent(Stamina / MaxStamina);
}

void UPlayerHUDWidget::OnMaxStaminaAttributeChange(float NewValue)
{
	MaxStamina = NewValue;
	StaminaBar->SetPercent(Stamina / MaxStamina);
}
