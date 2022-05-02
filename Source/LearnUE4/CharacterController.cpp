// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Blueprint/UserWidget.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (WBP_HUDCharacterStats) {
		HUDCharaterStats = CreateWidget<UUserWidget>(this, WBP_HUDCharacterStats);
		HUDCharaterStats->AddToViewport();
		HUDCharaterStats->SetVisibility(ESlateVisibility::Visible);
	}
}

