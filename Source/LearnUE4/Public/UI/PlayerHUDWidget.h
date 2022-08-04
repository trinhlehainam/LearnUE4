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
	UWidgetSwitcher* InteractUISwitcher;
	
	UFUNCTION()
	void OnHealthAttributeChange(float NewValue);
	void OnMaxHealthAttributeChange(float NewValue);

	float Health;
	float MaxHealth;
	float Mana;
	float MaxMana;
};
