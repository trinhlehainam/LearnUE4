// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
bool IInteractable::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return false;
}

float IInteractable::GetInteractionDuration_Implementation(UPrimitiveComponent* InteractedComponent) const
{
	return 0.f;
}

void IInteractable::PreInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent)
{
}

void IInteractable::PostInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent)
{
}

void IInteractable::CancelInteraction_Implementation()
{
}

void IInteractable::OnFoundNewTarget_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent)
{
}

void IInteractable::OnTargetLost_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent)
{
}
