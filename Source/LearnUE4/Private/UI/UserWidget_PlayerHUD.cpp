// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidget_PlayerHUD.h"

#include "Characters/PlayerCharacter.h"
#include "Components/ProgressBar.h"

void UUserWidget_PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUserWidget_PlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	APlayerCharacter* PlayerPawn = GetOwningPlayerPawn<APlayerCharacter>();

	check(PlayerPawn);

	PlayerPawn->OnHealthChange.AddDynamic(this, &UUserWidget_PlayerHUD::OnHealthAttributeChange);
	Health = PlayerPawn->GetHealth();
	MaxHealth = PlayerPawn->GetMaxHealth();

	if (HealthBar)
	{
		HealthBar->SetPercent(Health / MaxHealth);
	}
}

void UUserWidget_PlayerHUD::OnHealthAttributeChange(float NewValue)
{
	Health = NewValue;
	HealthBar->SetPercent(Health / MaxHealth);
}

void UUserWidget_PlayerHUD::OnMaxHealthAttributeChange(float NewValue)
{
	MaxHealth = NewValue;
	HealthBar->SetPercent(Health / MaxHealth);
}
