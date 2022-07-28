// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

class UInputMappingContext;
class UInputConfig;

/**
 * 
 */
UCLASS()
class LEARNUE4_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Reference to User Widget Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widgets)
	TSubclassOf<class UUserWidget> WBP_HUDCharacterStats;

	// Pointer to widget instance after creating it
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets)
	UUserWidget* HUDCharaterStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widgets)
	TSubclassOf<UUserWidget> WBP_PauseMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets)
	UUserWidget* PauseMenu;

	bool bIsPauseMenuVisible;

	UFUNCTION()
	void TogglePauseMenu();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void CreateHUD();

	void AddInputMappingContext();
private:
	
	UFUNCTION(BlueprintCallable)
	void DisplayPauseMenu();

	UFUNCTION(BlueprintCallable)
	void HidePauseMenu();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyboardInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* GamepadInputMappingContext;
};
