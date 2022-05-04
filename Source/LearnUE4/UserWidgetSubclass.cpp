// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetSubclass.h"

void UUserWidgetSubclass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind function for UWidget's delegate here
}

void UUserWidgetSubclass::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUserWidgetSubclass::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUserWidgetSubclass::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUserWidgetSubclass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
