// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CustomPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Abilities/CustomGameplayTags.h"
#include "Blueprint/UserWidget.h"
#include "Input/CustomEnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddInputMappingContexts();

	CreateHUD();
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	// TODO: Use CommonUI that has own Input Action Binding for control UI
	if (UCustomEnhancedInputComponent* EnhancedInputComponent = Cast<UCustomEnhancedInputComponent>(InputComponent))
	{
		// BUG: Value in static FCustomGameplayTags instance become null when recompile in Editor
		EnhancedInputComponent->BindActionByInputTag(
			InputConfig, FCustomGameplayTags::Get().InputTag_TogglePauseMenu,
			ETriggerEvent::Started, this, &ACustomPlayerController::TogglePauseMenu);
	}
}

void ACustomPlayerController::CreateHUD()
{
	if (PlayerHUDWidgetClass)
	{
		HUDCharaterStats = CreateWidget<UUserWidget>(this, PlayerHUDWidgetClass);
		HUDCharaterStats->AddToViewport();
		HUDCharaterStats->SetVisibility(ESlateVisibility::Visible);
	}

	bIsPauseMenuVisible = false;
	if (PauseMenuWidgetClass)
	{
		PauseMenu = CreateWidget(this, PauseMenuWidgetClass);
		PauseMenu->AddToViewport();
		// Hidden by default
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ACustomPlayerController::AddInputMappingContexts()
{
	// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(KeyboardInputMappingContext, 0);
		Subsystem->AddMappingContext(GamepadInputMappingContext, 0);
	}
}

void ACustomPlayerController::RemoveInputMappingContexts()
{
	// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(KeyboardInputMappingContext);
		Subsystem->RemoveMappingContext(GamepadInputMappingContext);
	}
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
		
		FInputModeGameAndUI InputModeGameAndUI;
		SetInputMode(InputModeGameAndUI);
		SetPause(true);
		
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		FLatentActionInfo LatentActionInfo;
		UKismetSystemLibrary::Delay(this, 0.1f, LatentActionInfo);
		// TODO: Prevent hardcoded
		PauseMenu->GetWidgetFromName("ResumeButton")->SetFocus();
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