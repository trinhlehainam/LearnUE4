// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CustomPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Input/CustomEnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/PauseMenuWidget.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateHUD();
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	// TODO: Use CommonUI that has own Input Action Binding for control UI
	InputComponent->BindKey(EKeys::P, IE_Pressed, this, &ACustomPlayerController::TogglePauseMenu)
	              .bExecuteWhenPaused = true;
	InputComponent->BindKey(EKeys::Gamepad_Special_Right, IE_Pressed, this, &ACustomPlayerController::TogglePauseMenu)
	              .bExecuteWhenPaused = true;
	InputComponent->BindKey(EKeys::AnyKey, IE_Pressed, this, &ACustomPlayerController::HandleSwitchUI)
	              .bExecuteWhenPaused = true;
}

void ACustomPlayerController::CreateHUD()
{
	if (PlayerHUDWidgetClass)
	{
		HUDCharaterStats = CreateWidget(this, PlayerHUDWidgetClass);
		HUDCharaterStats->AddToViewport();
		HUDCharaterStats->SetVisibility(ESlateVisibility::Visible);
	}

	bIsPauseMenuVisible = false;
	if (PauseMenuWidgetClass)
	{
		PauseMenu = CreateWidget<UPauseMenuWidget>(this, PauseMenuWidgetClass);
		PauseMenu->AddToViewport();
		// Hidden by default
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ACustomPlayerController::TogglePauseMenu(FKey Key)
{
	bIsPauseMenuVisible = !bIsPauseMenuVisible;
	bIsPauseMenuVisible ? DisplayPauseMenu(Key) : HidePauseMenu();
}

void ACustomPlayerController::DisplayPauseMenu(FKey Key)
{
	if (!IsValid(PauseMenu)) return;

	bIsPauseMenuVisible = true;
	bShowMouseCursor = true;

	SetPause(true);
	
	FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);

	PauseMenu->SetVisibility(ESlateVisibility::Visible);
	if (Key.IsGamepadKey())
	{
		bShowMouseCursor = false;

		FLatentActionInfo LatentActionInfo;
		UKismetSystemLibrary::Delay(this, 0.1f, LatentActionInfo);
		PauseMenu->ResumeButton->SetFocus();
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
		
		SetPause(false);
	}
}

void ACustomPlayerController::HandleSwitchUI(FKey Key)
{
	if (!IsValid(PauseMenu) || PauseMenu->Visibility == ESlateVisibility::Hidden) return;

	bShowMouseCursor = true;
	if (Key.IsGamepadKey())
	{
		bShowMouseCursor = false;
		if (!PauseMenu->HasAnyButtonFocus())
		{
			FLatentActionInfo LatentActionInfo;
			UKismetSystemLibrary::Delay(this, 0.1f, LatentActionInfo);
			PauseMenu->ResumeButton->SetFocus();
		}
	}
}