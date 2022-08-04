// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHudWidget.h"

#include "Characters/PlayerCharacter.h"
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

	APlayerCharacter* PlayerPawn = GetOwningPlayerPawn<APlayerCharacter>();

	check(PlayerPawn);

	PlayerPawn->OnHealthChange.AddDynamic(this, &UPlayerHUDWidget::OnHealthAttributeChange);
	Health = PlayerPawn->GetHealth();
	MaxHealth = PlayerPawn->GetMaxHealth();

	if (HealthBar)
		HealthBar->SetPercent(Health / MaxHealth);

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
