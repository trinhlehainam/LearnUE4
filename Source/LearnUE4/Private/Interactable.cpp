// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
bool IInteractable::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractingComponent)
{
	return false;
}

float IInteractable::GetInteractionDuration_Implementation() const
{
	return 0.f;
}
