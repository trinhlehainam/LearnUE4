// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
bool IInteractable::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return false;
}

bool IInteractable::HasRequiredGameplayTags_Implementation(const FGameplayTagContainer& InteractorTagContainer)
{
	return false;
}

float IInteractable::GetInteractionDuration_Implementation(UPrimitiveComponent* InteractedComponent) const
{
	return 0.f;
}

void IInteractable::BeginInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent, APlayerController* InteractingPlayerController)
{
}

void IInteractable::EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent, APlayerController* InteractingPlayerController)
{
}

void IInteractable::CancelInteraction_Implementation()
{
}

void IInteractable::OnNewTargetFound_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent)
{
}

void IInteractable::OnTargetLost_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent)
{
}
