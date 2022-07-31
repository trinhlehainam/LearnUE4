// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_InteractionHandle.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

#include "Interactable.h"
#include "Characters/BaseCharacter.h"

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

	ABaseCharacter* InteractingActor = Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get());

	if (!IsValid(InteractingActor))
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	TargetDataHandle = InteractingActor->GetInteractableTargetDataHandle();

	if (TargetDataHandle.Num() == 0)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
	AActor* InteractedActor = HitResult->GetActor();
	UPrimitiveComponent* InteractedComponent = HitResult->GetComponent();

	if (!IsValid(InteractedActor) || !InteractedActor->Implements<UInteractable>())
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	InteractionDuration = IInteractable::Execute_GetInteractionDuration(InteractedActor, InteractedComponent);

	if (InteractionDuration > 0.f)
	{
		UAbilityTask_WaitDelay* WaitUntilFinishInteractionTask = UAbilityTask_WaitDelay::WaitDelay(
			this, InteractionDuration);
		WaitUntilFinishInteractionTask->OnFinish.AddDynamic(this, &UGA_InteractionHandle::HandleFinishWaitInteraction);
		WaitUntilFinishInteractionTask->ReadyForActivation();

		UAbilityTask_WaitInputRelease* WaitInputReleaseTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
		WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGA_InteractionHandle::HandleOnInputRelease);
		WaitInputReleaseTask->ReadyForActivation();
	}
	else
	{
		IInteractable::Execute_PreInteract(InteractedActor, GetActorInfo().AvatarActor.Get(),
		                                   HitResult->GetComponent());

		// Interactable Target may perform Destroy itself when execute PreInteract
		if (!IsValid(InteractedActor))
			return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

		IInteractable::Execute_PostInteract(InteractedActor, GetActorInfo().AvatarActor.Get(),
		                                    HitResult->GetComponent());
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
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
	}
}

void UGA_InteractionHandle::HandleOnInputRelease(float TimeHold)
{
	if (TimeHold < InteractionDuration)
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UGA_InteractionHandle::HandleFinishWaitInteraction()
{
	PerformInteraction();
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

	// Interactable Target may perform Destroy itself when execute PreInteract
	if (!IsValid(InteractedActor))
		return CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);

	IInteractable::Execute_PostInteract(InteractedActor, GetActorInfo().AvatarActor.Get(),
	                                    HitResult->GetComponent());

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
