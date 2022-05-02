// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDPlayerStats.h"
#include "Components/ProgressBar.h"
#include "MyCharacter.h"

void UHUDPlayerStats::NativeConstruct()
{
	Super::NativeConstruct();

	if (!OwningCharacter)
		OwningCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());
}

void UHUDPlayerStats::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);

	UpdateHealthBarPercent();
}

void UHUDPlayerStats::UpdateHealthBarPercent()
{
	if (OwningCharacter)
		HealthBar->SetPercent(OwningCharacter->GetHealth() / OwningCharacter->GetMaxHealth());
}
