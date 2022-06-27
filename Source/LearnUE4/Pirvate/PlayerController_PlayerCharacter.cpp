// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_PlayerCharacter.h"
#include "Blueprint/UserWidget.h"

void APlayerController_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (WBP_HUDCharacterStats) {
		HUDCharaterStats = CreateWidget<UUserWidget>(this, WBP_HUDCharacterStats);
		HUDCharaterStats->AddToViewport();
		HUDCharaterStats->SetVisibility(ESlateVisibility::Visible);
	}

	bIsPauseMenuVisible = false;
	if (WBP_PauseMenu)
	{
		PauseMenu = CreateWidget(this, WBP_PauseMenu);
		PauseMenu->AddToViewport();
		// Hidden by default
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerController_PlayerCharacter::TogglePauseMenu()
{
	bIsPauseMenuVisible = !bIsPauseMenuVisible;
	bIsPauseMenuVisible ? DisplayPauseMenu() : HidePauseMenu();
}

void APlayerController_PlayerCharacter::DisplayPauseMenu()
{
	if (PauseMenu)
	{
		bIsPauseMenuVisible = true;
		bShowMouseCursor = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		FInputModeGameAndUI InputModeGameAndUI;
		SetInputMode(InputModeGameAndUI);
	}
}

void APlayerController_PlayerCharacter::HidePauseMenu()
{
	if (PauseMenu)
	{
		bIsPauseMenuVisible = false;
		bShowMouseCursor = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		FInputModeGameOnly InputModeGameOnly;
		SetInputMode(InputModeGameOnly);
	}
}

