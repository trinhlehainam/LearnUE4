// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableActorBase.h"
#include "ApplyEffectItem.generated.h"

UCLASS(Abstract)
class LEARNUE4_API AApplyEffectItem : public AInteractableActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AApplyEffectItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent, APlayerController* InteractingController) override;
};
