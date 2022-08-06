// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UWidgetSwitcher;
class UProgressBar;

/**
 * 
 */
UCLASS()
class LEARNUE4_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SwitchShowInteractUIText(bool bIsGamepadKey);

	UWidgetSwitcher* GetInteractWidget();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ManaBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* InteractUISwitcher;

	UFUNCTION()
	void OnHealthAttributeChange(float NewValue);
	
	UFUNCTION()
	void OnMaxHealthAttributeChange(float NewValue);
	
	UFUNCTION()
	void OnManaAttributeChange(float NewValue);
	
	UFUNCTION()
	void OnMaxManaAttributeChange(float NewValue);
	
	UFUNCTION()
	void OnStaminaAttributeChange(float NewValue);
	
	UFUNCTION()
	void OnMaxStaminaAttributeChange(float NewValue);

	float Health;
	float MaxHealth;
	float Mana;
	float MaxMana;
	float Stamina;
	float MaxStamina;
};
