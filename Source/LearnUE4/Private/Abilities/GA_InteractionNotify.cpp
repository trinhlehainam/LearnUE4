// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_InteractionNotify.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AT_WaitInteractableTarget.h"

UGA_InteractionNotify::UGA_InteractionNotify()
{
	bActivateOnGranted = true;
	MeshComponentVariableName = FName("Mesh");
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
		this, TraceChannel, TraceLocationType, SocketName, MeshComponentVariableName, TraceRange, FireRate, bShowDebug);

	if (!ScanInteractionTask) return;

	// WaitForInteractionTarget Task will clean up these delegates OnDestroy
	ScanInteractionTask->OnTargetLost.AddDynamic(this, &UGA_InteractionNotify::OnTargetLost);
	ScanInteractionTask->OnFoundNewTarget.AddDynamic(this, &UGA_InteractionNotify::OnFoundNewTarget);

	// Activate this task
	ScanInteractionTask->ReadyForActivation();
}

void UGA_InteractionNotify::OnFoundNewTarget_Implementation(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	FGameplayEventData EventData;
}

void UGA_InteractionNotify::OnTargetLost_Implementation(const FGameplayAbilityTargetDataHandle& DataHandle)
{
}
