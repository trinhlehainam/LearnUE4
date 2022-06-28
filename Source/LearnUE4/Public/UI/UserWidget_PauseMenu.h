// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_PauseMenu.generated.h"

class UButton;
class APlayerController_PlayerCharacter;

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
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoadButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	APlayerController_PlayerCharacter* PlayerController;

	UFUNCTION()
	void Resume();
	
	UFUNCTION()
	void Save();
	
	UFUNCTION()
	void Load();
	
	UFUNCTION()
	void Quit();
};
