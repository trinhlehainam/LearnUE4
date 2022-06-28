// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidget_PlayerHUD.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Characters/MyCharacter.h"

void UUserWidget_PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUserWidget_PlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!OwningCharacter)
		OwningCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());

	if (OwningCharacter)
	{
		OwningCharacter->OnHealthAttributeChange.AddDynamic(this, &UUserWidget_PlayerHUD::OnHealthAttributeChange);
		Health = OwningCharacter->GetHealth();
		MaxHealth = OwningCharacter->GetMaxHealth();
	}

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
