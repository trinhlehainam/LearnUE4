// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_InteractionNotify.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"

#include "Abilities/CustomGameplayTags.h"
#include "Abilities/Tasks/AT_WaitInteractableTarget.h"
#include "Interfaces/Interactable.h"
#include "Characters/BaseCharacter.h"
#include "Components/SlateWrapperTypes.h"
#include "Controllers/CustomPlayerController.h"

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
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	TraceTask = UAT_WaitInteractableTarget::WaitForInteractableTarget(
		this, TraceChannel, SourceTransformType, MeshSocketName, TraceRange, FireRate, bShowDebug,
		bUsePlayerControllerView);
	TraceTask->OnTargetLost.AddDynamic(this, &UGA_InteractionNotify::OnTargetLost);
	TraceTask->OnFoundNewTarget.AddDynamic(this, &UGA_InteractionNotify::OnFoundNewTarget);
	TraceTask->ReadyForActivation();

	UAbilityTask_WaitGameplayTagAdded* WaitTagAddedTask = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(
		this, ECustomGameplayTags::State_Interacting);
	WaitTagAddedTask->Added.AddDynamic(this, &UGA_InteractionNotify::OnInteractingTagAdded);
	WaitTagAddedTask->ReadyForActivation();	

	UAbilityTask_WaitGameplayTagRemoved* WaitTagRemovedTask = UAbilityTask_WaitGameplayTagRemoved::WaitGameplayTagRemove(
		this, ECustomGameplayTags::State_Interacting);
	WaitTagRemovedTask->Removed.AddDynamic(this, &UGA_InteractionNotify::OnInteractingTagRemoved);
	WaitTagRemovedTask->ReadyForActivation();
}

void UGA_InteractionNotify::OnFoundNewTarget(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	// TODO: Hardcoded for ACustomPlayerController
	if (ACustomPlayerController* PC = Cast<ACustomPlayerController>(CurrentActorInfo->PlayerController.Get()))
	{
		PC->SetInteractWidgetVisibility(ESlateVisibility::Visible);	
	}
	
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
	// TODO: Hardcoded for ACustomPlayerController
	if (ACustomPlayerController* PC = Cast<ACustomPlayerController>(CurrentActorInfo->PlayerController.Get()))
	{
		PC->SetInteractWidgetVisibility(ESlateVisibility::Hidden);	
	}
	
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

void UGA_InteractionNotify::OnInteractingTagAdded()
{
	if (!TraceTask.IsValid() || !TraceTask->IsActive()) return;
	TraceTask->PauseTrace();
}

void UGA_InteractionNotify::OnInteractingTagRemoved()
{
	if (!TraceTask.IsValid() || !TraceTask->IsActive()) return;
	TraceTask->ResumeTrace();
}

void UGA_InteractionNotify::SentUpdateTargetDataGameplayEvent(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	FGameplayEventData EventData;
	EventData.TargetData = DataHandle;
	SendGameplayEvent(ECustomGameplayTags::GameplayEvent_UpdateInteractableTargetData, EventData);
}