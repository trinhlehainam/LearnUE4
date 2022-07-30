// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_PauseMenu.generated.h"

class UButton;
class ACustomPlayerController;

/**
 * 
 */
UCLASS()
class LEARNUE4_API UUserWidget_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="PauseMenu")
	TSoftObjectPtr<UWorld> MainMenuLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UButton* MainMenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UButton* QuitButton;

	TArray<UButton*> ButtonLists;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	ACustomPlayerController* PlayerController;

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void ReturnToMainMenu();

	UFUNCTION()
	void Quit();
};
