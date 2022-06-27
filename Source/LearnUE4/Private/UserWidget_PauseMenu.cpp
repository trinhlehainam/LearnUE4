// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_PauseMenu.h"

#include "PlayerController_PlayerCharacter.h"
#include "MyCharacter.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Media/Public/IMediaControls.h"

void UUserWidget_PauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Controller = Cast<APlayerController_PlayerCharacter>(UGameplayStatics::GetPlayerController(this, 0));
	Character = Cast<AMyCharacter>(Controller->GetCharacter());

	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Resume);
	if (SaveButton) SaveButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Save);
	if (LoadButton) LoadButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Load);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::Quit);
}

void UUserWidget_PauseMenu::Resume()
{
	if (!Controller)
		Controller = Cast<APlayerController_PlayerCharacter>(UGameplayStatics::GetPlayerController(this, 0));
	else
	{
		Controller->TogglePauseMenu();
	}
}

void UUserWidget_PauseMenu::Save()
{
	if (!Character)
	{
		Character = Cast<AMyCharacter>(Controller->GetCharacter());
	}
	else
	{
		Character->SaveData();
	}
}

void UUserWidget_PauseMenu::Load()
{
	if (!Character)
	{
		Character = Cast<AMyCharacter>(Controller->GetCharacter());
	}
	else
	{
		Character->LoadData();
	}
}

void UUserWidget_PauseMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
