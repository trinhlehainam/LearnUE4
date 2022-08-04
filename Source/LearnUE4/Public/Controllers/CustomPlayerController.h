// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Interactor.h"
#include "CustomPlayerController.generated.h"

class UInputMappingContext;
class UInputConfig;
class UPauseMenuWidget;
class UPlayerHUDWidget;

/**
 * 
 */
UCLASS()
class LEARNUE4_API ACustomPlayerController : public APlayerController, public IInteractor
{
	GENERATED_BODY()
	
public:
	// Reference to User Widget Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widgets)
	TSubclassOf<class UUserWidget> PlayerHUDWidgetClass;

	// Pointer to widget instance after creating it
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets)
	UPlayerHUDWidget* PlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widgets)
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widgets)
	UPauseMenuWidget* PauseMenu;

	bool bIsPauseMenuVisible;

	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu(FKey Key);
	
	UFUNCTION(BlueprintCallable)
	void DisplayPauseMenu(FKey Key);

	UFUNCTION(BlueprintCallable)
	void HidePauseMenu();

	UFUNCTION(BlueprintCallable)
	void HandleSwitchUI(FKey Key);

	UFUNCTION(BlueprintCallable)
	void SetInteractWidgetVisibility(ESlateVisibility Visibility);

	// ~ Begin IInteractor Interface
	virtual void OnTargetLost_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent) override;
	virtual void OnNewTargetFound_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent) override;
	virtual void OnBeginInteraction_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent) override;
	virtual void OnEndInteraction_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent) override;
	// ~ End IInteractor Interface
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void CreateHUD();
};
