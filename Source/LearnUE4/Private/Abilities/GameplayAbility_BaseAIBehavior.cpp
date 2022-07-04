// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GameplayAbility_BaseAIBehavior.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Controllers/AIController_Enemy.h"

void UGameplayAbility_BaseAIBehavior::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayAbilitySpec& Spec)
{
	if (!ActorInfo) return;
	if (!ActorInfo->AvatarActor.IsValid()) return;

	AIController = Cast<AAIController_Enemy>(ActorInfo->AvatarActor->GetOwner());

	if (BehaviorTree && BehaviorTree->BlackboardAsset && AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		AIController->UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComp);
	}
}

bool UGameplayAbility_BaseAIBehavior::StartBehaviorTree()
{
	if (!BehaviorTree) return false;

	if (!AIController)
	{
		FGameplayAbilityActorInfo ActorInfo = GetActorInfo();
		if (!ActorInfo.OwnerActor.IsValid()) return false;

		AIController = Cast<AAIController_Enemy>(ActorInfo.OwnerActor->GetInstigatorController());
	}
	else
	{
		AIController->RunBehaviorTree(BehaviorTree);
	}

	return true;
}
