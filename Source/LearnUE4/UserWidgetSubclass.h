// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetSubclass.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UUserWidgetSubclass : public UUserWidget
{
	GENERATED_BODY()

protected:
	/**
	 * Called once only at game time on non-template instances.
	 * While Construct/Destruct pertain to the underlying Slate, this is called only once for the UUserWidget.
	 * If you have one-time things to establish up-front (like binding callbacks to events on BindWidget properties), do so here.
	 */
	virtual void NativeOnInitialized() override;

	/**
	 * Called by both the game and the editor.  Allows users to run initial setup for their widgets to better preview
	 * the setup in the designer and since generally that same setup code is required at runtime, it's called there
	 * as well.
	 *
	 * **WARNING**
	 * This is intended purely for cosmetic updates using locally owned data, you can not safely access any game related
	 * state, if you call something that doesn't expect to be run at editor time, you may crash the editor.
	 *
	 * In the event you save the asset with blueprint code that causes a crash on evaluation.  You can turn off
	 * PreConstruct evaluation in the Widget Designer settings in the Editor Preferences.
	 */
	virtual void NativePreConstruct() override;

	/**
	 * Called after the underlying slate widget is constructed.  Depending on how the slate object is used
	 * this event may be called multiple times due to adding and removing from the hierarchy.
	 * If you need a true called-once-when-created event, use OnInitialized.
	 */
	virtual void NativeConstruct() override;

	/**
	 * Called when a widget is no longer referenced causing the slate resource to destroyed.  Just like
	 * Construct this event can be called multiple times.
	 */
	virtual void NativeDestruct() override;

	/**
	 * Ticks this widget.  Override in derived classes, but always call the parent implementation.
	 *
	 * @param  MyGeometry The space allotted for this widget
	 * @param  InDeltaTime  Real time passed since last tick
	 */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
