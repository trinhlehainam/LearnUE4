// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableItem.h"
#include "GameFramework/Actor.h"
#include "ApplyEffectItem.generated.h"

UCLASS(Abstract)
class LEARNUE4_API AApplyEffectItem : public AInteractableItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AApplyEffectItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PreInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent) override;
};
