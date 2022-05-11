// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* LoadButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	class ACharacterController* Controller;
	class AMyCharacter* Character;

	UFUNCTION()
	void Resume();
	
	UFUNCTION()
	void Save();
	
	UFUNCTION()
	void Load();
	
	UFUNCTION()
	void Quit();
};
