// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;
class ACustomPlayerController;

/**
 * 
 */
UCLASS()
class LEARNUE4_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* QuitButton;

	bool HasAnyButtonFocus() const;
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="PauseMenu")
	TSoftObjectPtr<UWorld> MainMenuLevel;

	UPROPERTY()
	TArray<UButton*> Buttons;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	ACustomPlayerController* PlayerController;

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void ReturnToMainMenu();

	UFUNCTION()
	void Quit();
};
