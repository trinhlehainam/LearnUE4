// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActorBase.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class LEARNUE4_API AWeaponActor : public AInteractableActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponActor();

	UFUNCTION(BlueprintCallable)
	void SetEnableWeaponOverlapCollison(bool bEnable);
protected:

	virtual void EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
	                                             APlayerController* InteractingPlayerController) override;
	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;

	int8 bCanInteract:1;
};

