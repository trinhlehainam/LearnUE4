// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UUserWidget_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UFUNCTION()
	void OnHealthAttributeChange(float NewValue);
	void OnMaxHealthAttributeChange(float NewValue);

	float Health;
	float MaxHealth;
	float Mana;
	float MaxMana;
};
