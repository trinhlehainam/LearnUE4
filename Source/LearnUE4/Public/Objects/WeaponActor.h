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

	virtual void OnConstruction(const FTransform& Transform) override;

	void SetEnableCustomDepth(bool bEnable);
	
	void EnableGlowMaterial();
	void DisableGlowMaterial();

	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent) override;
	virtual void BeginInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
	                                             APlayerController* InteractingPlayerController) override;
	virtual void EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
	                                           APlayerController* InteractingPlayerController) override;
	virtual void CancelInteraction_Implementation() override;
	virtual void OnNewTargetFound_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent) override;
	virtual void OnTargetLost_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag DamageEventTag;

	int8 bCanInteract:1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Properties")
	int32 MaterialIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
	UMaterialInstanceDynamic* GlowDynamicMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	UMaterialInstance* GlowMaterialInstance;
};

