// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEARNUE4_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	bool IsAvailableForInteraction(UPrimitiveComponent* InteractedComponent);
	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	float GetInteractionDuration(UPrimitiveComponent* InteractedComponent) const;
	virtual float GetInteractionDuration_Implementation(UPrimitiveComponent* InteractedComponent) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	void PreInteract(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent);
	virtual void PreInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	void PostInteract(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent);
	virtual void PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	void CancelInteraction();
	virtual void CancelInteraction_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	void OnFoundNewTarget(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent);
	virtual void OnFoundNewTarget_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	void OnTargetLost(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent);
	virtual void OnTargetLost_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent);
};
