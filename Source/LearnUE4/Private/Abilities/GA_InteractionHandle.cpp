// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_InteractionHandle.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Effects/GE_AddInteractingTag.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

#include "Interfaces/Interactable.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/Interactor.h"

UGA_InteractionHandle::UGA_InteractionHandle()
{
	InteractionDuration = 0.f;
	AddInteractingTagEffectClass = UGE_AddInteractingTag::StaticClass();
}

void UGA_InteractionHandle::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	// TODO: Hard coded to update Target Data from GA_InteractingNotify to ABaseCharacter
	if (ABaseCharacter* InteractingActor = Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get())
	{
		if (!IsValid(InteractingActor))
			return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

		TargetDataHandle = InteractingActor->GetInteractableTargetDataHandle();
	}

	if (TargetDataHandle.Num() == 0)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
	AActor* InteractedActor = HitResult->GetActor();
	UPrimitiveComponent* InteractedComponent = HitResult->GetComponent();
	
	APlayerController* PC = ActorInfo->PlayerController.Get();
	AActor* InteractingActor = ActorInfo->AvatarActor.Get();

	if (!IsValid(InteractedActor) || !InteractedActor->Implements<UInteractable>())
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	if (IsValid(PC) && PC->Implements<IInteractor>())
		IInteractor::Execute_OnBeginInteraction(PC, InteractedActor, InteractedComponent);

	InteractionDuration = IInteractable::Execute_GetInteractionDuration(InteractedActor, InteractedComponent);

	// For Interactable Target triggers actions at start of interaction (like start animation, etc)
	IInteractable::Execute_BeginInteraction(InteractedActor, InteractingActor, InteractedComponent, PC);

	if (InteractionDuration > 0.f)
	{
		UAbilityTask_WaitDelay* WaitUntilFinishInteractionTask = UAbilityTask_WaitDelay::WaitDelay(
			this, InteractionDuration);
		WaitUntilFinishInteractionTask->OnFinish.AddDynamic(this, &UGA_InteractionHandle::OnEndInteraction);
		WaitUntilFinishInteractionTask->ReadyForActivation();

		UAbilityTask_WaitInputRelease* WaitInputReleaseTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
		WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGA_InteractionHandle::OnInputReleased);
		WaitInputReleaseTask->ReadyForActivation();

		// Apply State.Interacting Tag to Interactor to tell GA_InteractionNotify that this Actor is in Interacting State
		// GA_InteractionNotify is listening to Added and Removed of State.Interacting tag and will process accordingly
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		if (IsValid(ASC) && IsValid(AddInteractingTagEffectClass))
		{
			FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
				AddInteractingTagEffectClass, 1.f, ContextHandle);

			AddInteractingTagEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	else
	{
		if (IsValid(PC) && PC->Implements<IInteractor>())
			IInteractor::Execute_OnEndInteraction(PC, InteractedActor, InteractedComponent);

		// Interactable Target may perform Destroy itself when execute BeginInteraction
		if (!IsValid(InteractedActor))
			return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

		IInteractable::Execute_EndInteraction(InteractedActor, InteractingActor, InteractedComponent, PC);

		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
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
			IInteractable::Execute_CancelInteraction(InteractableActor);
	}

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (IsValid(ASC) && AddInteractingTagEffectHandle.IsValid())
	{
		ASC->RemoveActiveGameplayEffect(AddInteractingTagEffectHandle);
	}

	TargetDataHandle.Clear();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_InteractionHandle::OnUpdatedTargetData(FGameplayEventData Payload)
{
	const UAbilitySystemComponent* ASC = GetActorInfo().AbilitySystemComponent.Get();

	if (!ASC)
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UGA_InteractionHandle::OnInputReleased(float TimeHold)
{
	if (TimeHold < InteractionDuration)
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UGA_InteractionHandle::OnEndInteraction()
{
	const FHitResult* HitResult = TargetDataHandle.Get(0)->GetHitResult();
	AActor* InteractedActor = HitResult->GetActor();
	UPrimitiveComponent* InteractedComponent = HitResult->GetComponent();

	APlayerController* PC = CurrentActorInfo->PlayerController.Get();
	AActor* InteractingActor = CurrentActorInfo->AvatarActor.Get();

	if (IsValid(PC) && PC->Implements<IInteractor>())
		IInteractor::Execute_OnEndInteraction(PC, InteractedActor, InteractedComponent);

	// Interactable Target may perform Destroy itself when execute BeginInteraction
	if (!IsValid(InteractedActor))
		return CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);

	IInteractable::Execute_EndInteraction(InteractedActor, InteractingActor, InteractedComponent, PC);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
