// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CustomPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Input/CustomEnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/PauseMenuWidget.h"
#include "UI/PlayerHudWidget.h"

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
		PlayerHUD = CreateWidget<UPlayerHUDWidget>(this, PlayerHUDWidgetClass);
		PlayerHUD->AddToViewport();
		PlayerHUD->SetVisibility(ESlateVisibility::Visible);
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
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetInteractWidget())) return;
	PlayerHUD->SwitchShowInteractUIText(Key.IsGamepadKey());
	
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

void ACustomPlayerController::SetInteractWidgetVisibility(ESlateVisibility Visibility)
{
	if (!IsValid(PlayerHUD) || !IsValid(PlayerHUD->GetInteractWidget())) return;

	PlayerHUD->GetInteractWidget()->SetVisibility(Visibility);
}

void ACustomPlayerController::OnTargetLost_Implementation(AActor* InteractedActor,
	UPrimitiveComponent* InteractedComponent)
{
	SetInteractWidgetVisibility(ESlateVisibility::Hidden);
}

void ACustomPlayerController::OnNewTargetFound_Implementation(AActor* InteractedActor,
	UPrimitiveComponent* InteractedComponent)
{
	SetInteractWidgetVisibility(ESlateVisibility::Visible);
}

void ACustomPlayerController::OnBeginInteraction_Implementation(AActor* InteractedActor,
	UPrimitiveComponent* InteractedComponent)
{
	
}

void ACustomPlayerController::OnEndInteraction_Implementation(AActor* InteractedActor,
	UPrimitiveComponent* InteractedComponent)
{
	
}
