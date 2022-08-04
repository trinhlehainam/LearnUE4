// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetingTransformType.h"
#include "Abilities/BaseGameplayAbility.h"
#include "GA_InteractionNotify.generated.h"

class UAT_WaitInteractableTarget;

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGA_InteractionNotify : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_InteractionNotify();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnNewTargetFound(const FGameplayAbilityTargetDataHandle& DataHandle);
	
	UFUNCTION()
	void OnTargetLost(const FGameplayAbilityTargetDataHandle& DataHandle);

	UFUNCTION()
	void OnInteractingTagAdded();

	UFUNCTION()
	void OnInteractingTagRemoved();
	
	void SentUpdateTargetDataGameplayEvent(const FGameplayAbilityTargetDataHandle& DataHandle);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	EGameplayAbilityTargetingTransformType SourceTransformType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(DisplayName="Mesh's Socket Name"))
	FName MeshSocketName;
	
	// Use Player Controller's View Transform (aka Camera) to perform additional trace to only accept Interactable Target at center of the screen
	// Only work when Actor owning this ability is controlled by Player Controller and use Line Trace
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction", meta=(DisplayName="Use Player Controller's View"))
	bool bUsePlayerControllerView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float TraceRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float FireRate;

	TWeakObjectPtr<UAT_WaitInteractableTarget> TraceTask;
};
