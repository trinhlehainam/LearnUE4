// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InteractableItem.h"


// Sets default values
AInteractableItem::AInteractableItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AInteractableItem::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return true;
}

bool AInteractableItem::HasRequiredGameplayTags_Implementation(const FGameplayTagContainer& InteractorTagContainer)
{
	return InteractorTagContainer.HasAllExact(RequireTags);
}
