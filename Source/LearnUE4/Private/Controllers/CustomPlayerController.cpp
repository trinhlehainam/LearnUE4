// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CustomPlayerController.h"
#include "Blueprint/UserWidget.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (WBP_HUDCharacterStats)
	{
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

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAction("TogglePauseMenu", IE_Pressed, this,
	                           &ACustomPlayerController::TogglePauseMenu);
}

void ACustomPlayerController::TogglePauseMenu()
{
	bIsPauseMenuVisible = !bIsPauseMenuVisible;
	bIsPauseMenuVisible ? DisplayPauseMenu() : HidePauseMenu();
}

void ACustomPlayerController::DisplayPauseMenu()
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

void ACustomPlayerController::HidePauseMenu()
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
