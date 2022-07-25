// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidget_PauseMenu.h"

#include "Controllers/CustomPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUserWidget_PauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerController = GetOwningPlayer<ACustomPlayerController>();

	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Resume);
	if (SaveButton) SaveButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Save);
	if (LoadButton) LoadButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Load);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Quit);
}

void UUserWidget_PauseMenu::Resume()
{
	if (!PlayerController)
		PlayerController = GetOwningPlayer<ACustomPlayerController>();
	else
		PlayerController->TogglePauseMenu();
}

void UUserWidget_PauseMenu::Save()
{
}

void UUserWidget_PauseMenu::Load()
{
}

void UUserWidget_PauseMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
