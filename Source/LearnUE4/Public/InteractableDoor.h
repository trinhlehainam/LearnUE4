// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"

UCLASS()
class LEARNUE4_API AInteractableDoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent) override;
	virtual bool HasRequiredGameplayTags_Implementation(const FGameplayTagContainer& InteractorTagContainer) override;

	void UpdateDoorLocation(float Delta);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent* DoorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent* SwitchMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interact", meta=(AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> ApplyEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interact", meta=(AllowPrivateAccess))
	FGameplayTagContainer RequireTags;
};