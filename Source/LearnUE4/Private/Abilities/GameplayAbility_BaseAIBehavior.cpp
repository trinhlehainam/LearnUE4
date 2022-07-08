// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GameplayAbility_BaseAIBehavior.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Controllers/NPCController.h"

void UGameplayAbility_BaseAIBehavior::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilitySpec& Spec)
{
	if (!ActorInfo) return;
	if (!ActorInfo->AvatarActor.IsValid()) return;

	// Owner of a Character class is a Controller
	AIController = Cast<ANPCController>(ActorInfo->AvatarActor->GetOwner());
}

bool UGameplayAbility_BaseAIBehavior::StartBehaviorTree()
{
	if (!BehaviorTree) return false;

	if (!AIController.IsValid())
	{
		FGameplayAbilityActorInfo ActorInfo = GetActorInfo();
		if (!ActorInfo.OwnerActor.IsValid()) return false;

		AIController = Cast<ANPCController>(ActorInfo.AvatarActor->GetOwner());

		if (!AIController.IsValid()) return false;
	}
	else
	{
		AIController->RunBehaviorTree(BehaviorTree);
	}

	return true;
}
