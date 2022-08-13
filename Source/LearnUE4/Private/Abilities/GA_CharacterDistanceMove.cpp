#include "Abilities/GA_CharacterDistanceMove.h"

#include "Abilities/Tasks/AT_Timeline.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"

UGA_CharacterDistanceMove::UGA_CharacterDistanceMove()
{
	SectionName = FName("Default");

	bIgnoreMoveInput = true;
	bIgnoreLookInput = false;
}

void UGA_CharacterDistanceMove::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilityActivationInfo ActivationInfo,
                                                const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	if (!IsValid(DistanceMultiplerCurveFloat) || !IsValid(AnimMontage))
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get()))
	{
		ForwardVector = bUseMovementInputVectorDirection
			                ? Character->GetLastMovementInputVector().GetSafeNormal()
			                : Character->GetActorForwardVector();

		// TODO:
		// We can't control Character's direction with Velocity while Character's performing Root Motion
		// So we change Character's direction before apply Root Motion (Play Montage)
		if (bUseMovementInputVectorDirection)
			Character->SetActorRotation(ForwardVector.Rotation());
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	TimelineTask = UAT_Timeline::CreateTimelineTask(this);

	const float Duration = AnimInstance->Montage_Play(AnimMontage);
	if (Duration == 0.f)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	if (APlayerController* PC = ActorInfo->PlayerController.Get())
	{
		if (bIgnoreMoveInput) PC->SetIgnoreMoveInput(true);
		if (bIgnoreLookInput) PC->SetIgnoreLookInput(true);
	}

	if (SectionName != NAME_None)
	{
		AnimInstance->Montage_JumpToSection(SectionName, AnimMontage);
		TimelineTask->SetTimelineLength(AnimMontage->GetSectionLength(AnimMontage->GetSectionIndex(SectionName)));
	}

	FOnTimelineFloat OnTimelineFloatUpdate;
	FOnTimelineEvent OnTimelineFinished;

	OnTimelineFloatUpdate.BindDynamic(this, &UGA_CharacterDistanceMove::OnTimelineFloatTrackUpdate);
	OnTimelineFinished.BindDynamic(this, &UGA_CharacterDistanceMove::OnTimelineFinished);

	TimelineTask->AddInterpFloat(DistanceMultiplerCurveFloat, OnTimelineFloatUpdate);
	TimelineTask->SetTimelineFinishedFunc(OnTimelineFinished);

	TimelineTask->PlayFromStart();

	// TODO: Maybe use TimerMananger to Tick Timeline instead of TickTask
	// OwnerTaskComponent only register TickingTask in Activation NOT while TickComponent
	// So set up bTickingTask of AbilityTask before Activation to enable TickTask
	TimelineTask->ReadyForActivation();
}

void UGA_CharacterDistanceMove::OnTimelineFloatTrackUpdate(float LengthMultipler)
{
	if (UMovementComponent* MoveComp = CurrentActorInfo->MovementComponent.Get())
	{
		FVector CurrentVelocity = BaseVelocityLength * LengthMultipler * ForwardVector;
		MoveComp->Velocity.X = CurrentVelocity.X;
		MoveComp->Velocity.Y = CurrentVelocity.Y;
	}
}

void UGA_CharacterDistanceMove::OnTimelineFinished()
{
	if (APlayerController* PC = CurrentActorInfo->PlayerController.Get())
	{
		if (bIgnoreMoveInput) PC->SetIgnoreMoveInput(false);
		if (bIgnoreLookInput) PC->SetIgnoreLookInput(false);
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
