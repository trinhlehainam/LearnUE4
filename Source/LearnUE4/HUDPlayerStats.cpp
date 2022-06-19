// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDPlayerStats.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "MyCharacter.h"

void UHUDPlayerStats::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHUDPlayerStats::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!OwningCharacter)
		OwningCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());

	if (OwningCharacter)
	{
		OwningCharacter->OnHealthAttributeChange.AddDynamic(this, &UHUDPlayerStats::OnHealthAttributeChange);
		Health = OwningCharacter->GetHealth();
		MaxHealth = OwningCharacter->GetMaxHealth();
	}

	if (HealthBar)
	{
		HealthBar->SetPercent(Health / MaxHealth);
	}
}

void UHUDPlayerStats::OnHealthAttributeChange(float NewValue)
{
	Health = NewValue;
	HealthBar->SetPercent(Health / MaxHealth);
}

void UHUDPlayerStats::OnMaxHealthAttributeChange(float NewValue)
{
	MaxHealth = NewValue;
	HealthBar->SetPercent(Health / MaxHealth);
}
