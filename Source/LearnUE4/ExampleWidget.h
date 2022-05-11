// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExampleWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UExampleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
private:
	UPROPERTY(meta=(BindWidget))
	class UButton* Button;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text;
};
