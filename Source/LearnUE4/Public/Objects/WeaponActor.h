// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActorBase.h"
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

	UFUNCTION()
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                          AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);
protected:
	virtual void BeginPlay() override;

	virtual void EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
	                                           APlayerController* InteractingPlayerController) override;
	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag DamageEventTag;
	
	int8 bCanInteract:1;
};
