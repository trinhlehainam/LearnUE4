// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ApplyEffectItem.h"


// Sets default values
AApplyEffectItem::AApplyEffectItem()
{
}

// Called when the game starts or when spawned
void AApplyEffectItem::BeginPlay()
{
	Super::BeginPlay();
}

void AApplyEffectItem::EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
                                                     APlayerController* InteractingController)
{
	if (ApplyEffectsToInteractor(InteractingActor))
		Destroy();
}
