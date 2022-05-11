// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"

#include "CharacterController.h"
#include "MyCharacter.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Media/Public/IMediaControls.h"

void UPauseMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Controller = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	Character = Cast<AMyCharacter>(Controller->GetCharacter());

	if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Resume);
	if (SaveButton) SaveButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Save);
	if (LoadButton) LoadButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Load);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Quit);
}

void UPauseMenuWidget::Resume()
{
	if (!Controller)
		Controller = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	else
	{
		Controller->TogglePauseMenu();
	}
}

void UPauseMenuWidget::Save()
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

void UPauseMenuWidget::Load()
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

void UPauseMenuWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
