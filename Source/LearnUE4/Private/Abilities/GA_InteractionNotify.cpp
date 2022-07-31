// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_InteractionNotify.h"

#include "AbilitySystemComponent.h"
#include "Objects/Interactable.h"
#include "Abilities/CustomGameplayTags.h"
#include "Abilities/Tasks/AT_WaitInteractableTarget.h"
#include "Characters/BaseCharacter.h"

UGA_InteractionNotify::UGA_InteractionNotify()
{
	bActivateOnGranted = true;
	bUsePlayerControllerView = true;
	TraceRange = 200.f;
	FireRate = 0.1f;
}

void UGA_InteractionNotify::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	UAT_WaitInteractableTarget* ScanInteractionTask = UAT_WaitInteractableTarget::WaitForInteractableTarget(
		this, TraceChannel, SourceTransformType, MeshSocketName, TraceRange, FireRate, bShowDebug, bUsePlayerControllerView);

	// WaitForInteractionTarget Task will clean up these delegates OnDestroy
	ScanInteractionTask->OnTargetLost.AddDynamic(this, &UGA_InteractionNotify::OnTargetLost);
	ScanInteractionTask->OnFoundNewTarget.AddDynamic(this, &UGA_InteractionNotify::OnFoundNewTarget);
	//

	// Activate this task
	ScanInteractionTask->ReadyForActivation();
}

void UGA_InteractionNotify::OnFoundNewTarget(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	const FHitResult* HitResult = DataHandle.Get(0)->GetHitResult();
	AActor* InteractedActor = HitResult->GetActor();

	if (IsValid(InteractedActor) && InteractedActor->Implements<UInteractable>())
	{
		IInteractable::Execute_OnFoundNewTarget(InteractedActor, GetCurrentActorInfo()->AvatarActor.Get(),
		                                        HitResult->GetComponent());
	}

	// TODO: Hard coded to update Target Data from GA_InteractingNotify to ABaseCharacter
	if (ABaseCharacter* InteractingActor = Cast<ABaseCharacter>(CurrentActorInfo->AvatarActor.Get()))
	{
		InteractingActor->SetInteractableTargetDataHandle(DataHandle);
	}

	SentUpdateTargetDataGameplayEvent(DataHandle);
}

void UGA_InteractionNotify::OnTargetLost(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	const FHitResult* HitResult = DataHandle.Get(0)->GetHitResult();
	AActor* InteractedActor = HitResult->GetActor();

	if (IsValid(InteractedActor) && InteractedActor->Implements<UInteractable>())
	{
		IInteractable::Execute_OnTargetLost(InteractedActor, GetCurrentActorInfo()->AvatarActor.Get(),
		                                    HitResult->GetComponent());
	}

	// TODO: Implement better solution to handle UpdateTargetData when TargetLost
	// Hard coded to update Target Data from GA_InteractingNotify to ABaseCharacter
	if (ABaseCharacter* InteractingActor = Cast<ABaseCharacter>(CurrentActorInfo->AvatarActor.Get()))
	{
		InteractingActor->SetInteractableTargetDataHandle(FGameplayAbilityTargetDataHandle());
	}

	SentUpdateTargetDataGameplayEvent(FGameplayAbilityTargetDataHandle());
}

void UGA_InteractionNotify::SentUpdateTargetDataGameplayEvent(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	FGameplayEventData EventData;
	EventData.TargetData = DataHandle;
	SendGameplayEvent(FCustomGameplayTags::Get().GameplayEvent_UpdateInteractableTargetData, EventData);
}