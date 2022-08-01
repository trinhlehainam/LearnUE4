// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interactable.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

class UGameplayEffect;

UCLASS()
class LEARNUE4_API AInteractableItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableItem();

protected:
	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent) override;
	virtual bool HasRequiredGameplayTags_Implementation(const FGameplayTagContainer& InteractorTagContainer) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact", meta=(AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> ApplyEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact", meta=(AllowPrivateAccess))
	FGameplayTagContainer RequireTags;
};
