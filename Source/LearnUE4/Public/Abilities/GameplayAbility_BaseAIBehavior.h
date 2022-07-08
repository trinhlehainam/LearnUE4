// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "AI/BTTask_EnemyMoveToLocation.h"
#include "GameplayAbility_BaseAIBehavior.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGameplayAbility_BaseAIBehavior : public UBaseGameplayAbility
{
	GENERATED_BODY()

protected:
	// Initialize AI related Components of AIController (Blackboard, BehaviorTree)
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UFUNCTION(BlueprintCallable)
	bool StartBehaviorTree();
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="AI")
	UBehaviorTree* BehaviorTree;

	// Cached AIController object
	TWeakObjectPtr<class ANPCController> AIController;
};
