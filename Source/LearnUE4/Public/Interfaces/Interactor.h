// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactor.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractor : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implement this to an Actor perform Interact to receive Interaction information
 */
class LEARNUE4_API IInteractor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void OnNewTargetFound(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	virtual void OnNewTargetFound_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void OnTargetLost(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	virtual void OnTargetLost_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void OnBeginInteraction(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	virtual void OnBeginInteraction_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void OnEndInteraction(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
	virtual void OnEndInteraction_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent);
};
