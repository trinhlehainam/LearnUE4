// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDPlayerStats.h"
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

	if (HealthBar) {
		HealthBar->PercentDelegate.BindDynamic(this, &UHUDPlayerStats::GetHealthBarPercent);
		if (OwningCharacter)
			HealthBar->SetPercent(OwningCharacter->GetHealth() / OwningCharacter->GetMaxHealth());
	}
}

float UHUDPlayerStats::GetHealthBarPercent()
{
	if (!OwningCharacter)
		OwningCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());
	else
		return OwningCharacter->GetHealth() / OwningCharacter->GetMaxHealth();

	return HealthBar->Percent;
}
