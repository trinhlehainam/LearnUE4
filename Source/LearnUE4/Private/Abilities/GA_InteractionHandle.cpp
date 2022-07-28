// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_InteractionHandle.h"

#include "Abilities/CustomGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

#include "Interactable.h"

UGA_InteractionHandle::UGA_InteractionHandle()
{
	InteractionDuration = 0.f;
}

void UGA_InteractionHandle::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	// Listen UpdateDataEvent Gameplay Event sent from GA_InteractionNotify
	UAbilityTask_WaitGameplayEvent* UpdateTargetDataEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, FCustomGameplayTags::Get().GameplayEvent_UpdateInteractableTargetData);
	if (!UpdateTargetDataEventTask)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	UpdateTargetDataEventTask->EventReceived.AddDynamic(this, &UGA_InteractionHandle::OnUpdatedTargetData);
	UpdateTargetDataEventTask->ReadyForActivation();
	//

	UAbilityTask_WaitInputRelease* WaitInputReleaseTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!WaitInputReleaseTask)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGA_InteractionHandle::HandleOnInputRelease);
	WaitInputReleaseTask->ReadyForActivation();
}

void UGA_InteractionHandle::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo,
                                       bool bReplicateEndAbility, bool bWasCancelled)
{
	if (TargetDataHandle.Num() > 0)
	{
		const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
		AActor* InteractableActor = HitResult->GetActor();

		if (IsValid(InteractableActor) && InteractableActor->Implements<UInteractable>())
		{
			IInteractable::Execute_CancelInteraction(InteractableActor);
		}
	}

	TargetDataHandle.Clear();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_InteractionHandle::OnUpdatedTargetData(FGameplayEventData Payload)
{
	const UAbilitySystemComponent* ASC = GetActorInfo().AbilitySystemComponent.Get();

	if (!ASC)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}

	// TargetDataHandle is empty only when it hasn't yet initialized
	if (TargetDataHandle.Num() == 0)
	{
		// If there isn't any TargetData received from GA_InteractionNotify mean
		// Target is lost and hasn't found new one
		if (Payload.TargetData.Num() == 0)
		{
			CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
			return;
		}

		// Update Target Data
		TargetDataHandle = Payload.TargetData;

		const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
		AActor* InteractedActor = HitResult->GetActor();

		if (!IsValid(InteractedActor) || !InteractedActor->Implements<UInteractable>())
		{
			CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
			return;
		}

		InteractionDuration = IInteractable::Execute_GetInteractionDuration(InteractedActor, HitResult->GetComponent());

		if (InteractionDuration > 0.f)
		{
			UAbilityTask_WaitDelay* WaitDelay = UAbilityTask_WaitDelay::WaitDelay(this, InteractionDuration);
			WaitDelay->OnFinish.AddDynamic(this, &UGA_InteractionHandle::HandleWaitDelay);
			WaitDelay->ReadyForActivation();
			return;
		}

		IInteractable::Execute_PreInteract(InteractedActor, GetActorInfo().AvatarActor.Get(),
		                                   HitResult->GetComponent());
		IInteractable::Execute_PostInteract(InteractedActor, GetActorInfo().AvatarActor.Get(),
		                                    HitResult->GetComponent());

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
	else
	{
		// Lost Target
		if (Payload.TargetData.Num() == 0)
		{
			CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
			return;
		}

		const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
		const FHitResult* UpdatedHitResult = Payload.TargetData.Get(0)->GetHitResult();

		// Found New Target
		if (HitResult->GetActor() != UpdatedHitResult->GetActor())
		{
			CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		}
	}
}

void UGA_InteractionHandle::HandleOnInputRelease(float TimeHold)
{
	if (TimeHold < InteractionDuration)
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UGA_InteractionHandle::HandleWaitDelay()
{
}

void UGA_InteractionHandle::PerformInteraction()
{
	const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
	AActor* InteractedActor = HitResult->GetActor();

	if (!IsValid(InteractedActor) || !InteractedActor->Implements<UInteractable>())
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}
	
	IInteractable::Execute_PreInteract(InteractedActor, GetActorInfo().AvatarActor.Get(),
									   HitResult->GetComponent());
	IInteractable::Execute_PostInteract(InteractedActor, GetActorInfo().AvatarActor.Get(),
										HitResult->GetComponent());
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}