// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_InteractionHandle.h"

#include "Interactable.h"
#include "Abilities/CustomGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UGA_InteractionHandle::UGA_InteractionHandle()
{
}

void UGA_InteractionHandle::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	// Listen UpdateDataEvent Gameplay Event sent from GA_InteractionNotify
	UAbilityTask_WaitGameplayEvent* UpdateTargetDataEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this, FCustomGameplayTags::Get().UpdateInteractableTargetDataEvent);

	if (!UpdateTargetDataEvent)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	
	UpdateTargetDataEvent->EventReceived.AddDynamic(this, &UGA_InteractionHandle::OnUpdatedTargetData);

	UpdateTargetDataEvent->ReadyForActivation();
	//
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
	const FGameplayAbilitySpecHandle SpecHandle = GetCurrentAbilitySpecHandle();
	const FGameplayAbilityActorInfo ActorInfo = GetActorInfo();
	const FGameplayAbilityActivationInfo ActivationInfo = GetCurrentActivationInfo();
	const UAbilitySystemComponent* ASC = ActorInfo.AbilitySystemComponent.Get();

	if (!ASC)
	{
		CancelAbility(SpecHandle, &ActorInfo, ActivationInfo, true);
		return;
	}

	// TargetDataHandle is empty only when it hasn't yet initialized
	if (TargetDataHandle.Num() == 0)
	{
		// If there isn't any TargetData received from GA_InteractionNotify mean
		// Target is lost and hasn't found new one
		if (Payload.TargetData.Num() == 0)
		{
			CancelAbility(SpecHandle, &ActorInfo, ActivationInfo, true);
			return;
		}

		// Update Target Data
		TargetDataHandle = Payload.TargetData;

		const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
		AActor* InteractedActor = HitResult->GetActor();

		if (!IsValid(InteractedActor) || !InteractedActor->Implements<UInteractable>())
		{
			CancelAbility(SpecHandle, &ActorInfo, ActivationInfo, true);
			return;
		}

		// TODO: Handle case when Interaction Duration > 0.0f
		// float InteractionDuration = IInteractable::Execute_GetInteractionDuration(InteractedActor);
		
		IInteractable::Execute_PreInteract(InteractedActor, ActorInfo.AvatarActor.Get(), HitResult->GetComponent());
		IInteractable::Execute_PostInteract(InteractedActor, ActorInfo.AvatarActor.Get(), HitResult->GetComponent());

		EndAbility(SpecHandle, &ActorInfo, ActivationInfo, true, false);
	}
	else
	{
		// Lost Target
		if (Payload.TargetData.Num() == 0)
		{
			CancelAbility(SpecHandle, &ActorInfo, ActivationInfo, true);
			return;
		}

		const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
		const FHitResult* UpdatedHitResult = Payload.TargetData.Get(0)->GetHitResult();

		// Found New Target
		if (HitResult->GetActor() != UpdatedHitResult->GetActor())
		{
			CancelAbility(SpecHandle, &ActorInfo, ActivationInfo, true);
		}
	}
}
