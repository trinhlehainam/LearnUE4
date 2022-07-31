// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuWidget.h"

#include "Controllers/CustomPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UPauseMenuWidget::HasAnyButtonFocus() const
{
	for (const UButton* Button : Buttons)
		if (Button->HasUserFocus(GetOwningPlayer()))
			return true;	

	return false;
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = GetOwningPlayer<ACustomPlayerController>();

	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Resume);
	if (MainMenuButton) MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ReturnToMainMenu);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Quit);

	// TODO: Prevent Hardcoded
	Buttons.Reset(3);
	Buttons.Add(ResumeButton);
	Buttons.Add(MainMenuButton);
	Buttons.Add(QuitButton);
}

void UPauseMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (UButton* Button : Buttons)
	{
		FLinearColor BackgroundColor = Button->HasKeyboardFocus()
			                               ? FLinearColor(128, 0, 0, 255)
			                               : FLinearColor(128, 128, 128, 255);
		Button->SetBackgroundColor(BackgroundColor);
	}
}

void UPauseMenuWidget::Resume()
{
	if (!PlayerController)
		PlayerController = GetOwningPlayer<ACustomPlayerController>();
	else
		PlayerController->HidePauseMenu();
}

void UPauseMenuWidget::ReturnToMainMenu()
{
	FInputModeGameOnly InputModeGameOnly;
	PlayerController->SetInputMode(InputModeGameOnly);
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
	RemoveFromParent();
}

void UPauseMenuWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
