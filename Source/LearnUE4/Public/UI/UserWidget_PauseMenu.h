// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UUserWidget_PauseMenu : public UUserWidget
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

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	class APlayerController_PlayerCharacter* Controller;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
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
