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

	UFUNCTION(BlueprintCallable)
	void UpdateDoorLocation(float Z_Offset);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UStaticMeshComponent* DoorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UStaticMeshComponent* SwitchMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact", meta=(AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> ApplyEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interact", meta=(AllowPrivateAccess))
	FGameplayTagContainer RequireTags;

	FVector DoorStartLocation;
};