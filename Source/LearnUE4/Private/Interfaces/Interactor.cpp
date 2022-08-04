// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactor.h"


// Add default functionality here for any IInteractionUI functions that are not pure virtual.
void IInteractor::OnNewTargetFound_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent)
{
}

void IInteractor::OnTargetLost_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent)
{
}

void IInteractor::OnBeginInteraction_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent)
{
}

void IInteractor::OnEndInteraction_Implementation(AActor* InteractedActor, UPrimitiveComponent* InteractedComponent)
{
}
