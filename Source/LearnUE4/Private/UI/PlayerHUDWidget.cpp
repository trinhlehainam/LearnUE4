// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHudWidget.h"

#include "Characters/PlayerCharacter.h"
#include "Components/ProgressBar.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	APlayerCharacter* PlayerPawn = GetOwningPlayerPawn<APlayerCharacter>();

	check(PlayerPawn);

	PlayerPawn->OnHealthChange.AddDynamic(this, &UPlayerHUDWidget::OnHealthAttributeChange);
	Health = PlayerPawn->GetHealth();
	MaxHealth = PlayerPawn->GetMaxHealth();

	if (HealthBar)
	{
		HealthBar->SetPercent(Health / MaxHealth);
	}
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
