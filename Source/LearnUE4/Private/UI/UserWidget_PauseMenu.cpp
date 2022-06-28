// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidget_PauseMenu.h"

#include "Controllers/PlayerController_PlayerCharacter.h"
#include "Characters/MyCharacter.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUserWidget_PauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerController = GetOwningPlayer<APlayerController_PlayerCharacter>();

	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Resume);
	if (SaveButton) SaveButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Save);
	if (LoadButton) LoadButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Load);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Quit);
}

void UUserWidget_PauseMenu::Resume()
{
	if (!PlayerController)
		PlayerController = GetOwningPlayer<APlayerController_PlayerCharacter>();
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
