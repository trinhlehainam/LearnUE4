// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidget_PauseMenu.h"

#include "Controllers/CustomPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUserWidget_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = GetOwningPlayer<ACustomPlayerController>();

	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Resume);
	if (MainMenuButton) MainMenuButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::ReturnToMainMenu);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Quit);

	// TODO: Prevent Hardcoded
	ButtonLists.Reset(3);
	ButtonLists.Add(ResumeButton);
	ButtonLists.Add(MainMenuButton);
	ButtonLists.Add(QuitButton);
}

void UUserWidget_PauseMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (UButton* Button : ButtonLists)
	{
		FLinearColor BackgroundColor = Button->HasKeyboardFocus()
			                               ? FLinearColor(128, 0, 0, 255)
			                               : FLinearColor(128, 128, 128, 255);
		Button->SetBackgroundColor(BackgroundColor);
	}
}

void UUserWidget_PauseMenu::Resume()
{
	if (!PlayerController)
		PlayerController = GetOwningPlayer<ACustomPlayerController>();
	else
		PlayerController->TogglePauseMenu();
}

void UUserWidget_PauseMenu::ReturnToMainMenu()
{
	FInputModeGameOnly InputModeGameOnly;
	PlayerController->SetInputMode(InputModeGameOnly);
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
	RemoveFromParent();
}

void UUserWidget_PauseMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
