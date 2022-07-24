// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_ScanInteractPassive.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AT_WaitForInteractableTarget.h"

UGA_ScanInteractPassive::UGA_ScanInteractPassive()
{
	bActivateOnGranted = true;
	MeshComponentVariableName = FName("Mesh");
	TraceRange = 200.f;
	FireRate = 0.1f;
}

void UGA_ScanInteractPassive::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo,
                                              const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	UAT_WaitForInteractableTarget* ScanInteractionTask = UAT_WaitForInteractableTarget::WaitForInteractableTarget(
		this, TraceChannel, TraceLocationType, SocketName, MeshComponentVariableName, TraceRange, FireRate, bShowDebug);

	if (!ScanInteractionTask) return;

	// WaitForInteractionTarget Task will clean up these delegates OnDestroy
	ScanInteractionTask->OnTargetLost.AddDynamic(this, &UGA_ScanInteractPassive::OnTargetLost);
	ScanInteractionTask->OnFoundNewTarget.AddDynamic(this, &UGA_ScanInteractPassive::OnFoundNewTarget);

	// Activate this task
	ScanInteractionTask->ReadyForActivation();
}

void UGA_ScanInteractPassive::OnFoundNewTarget_Implementation(const FGameplayAbilityTargetDataHandle& DataHandle)
{
}

void UGA_ScanInteractPassive::OnTargetLost_Implementation(const FGameplayAbilityTargetDataHandle& DataHandle)
{
}
