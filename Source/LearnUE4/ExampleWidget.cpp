// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleWidget.h"

#include "Components/TextBlock.h"

void UExampleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UExampleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExampleText)
		ExampleText->SetText(FText::FromString(TEXT("Example Text")));
}
