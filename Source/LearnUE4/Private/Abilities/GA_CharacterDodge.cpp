#include "Abilities/GA_CharacterDodge.h"

#include "Abilities/Tasks/AT_Timeline.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGA_CharacterDodge::UGA_CharacterDodge()
{
	SectionName = FName("Default");
	
	bIgnoreMoveInput = true;
	bIgnoreLookInput = false;
}

void UGA_CharacterDodge::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	if (!IsValid(DistanceCurveFloat) || !IsValid(AnimMontage))
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	TimelineTask = UAT_Timeline::CreateTimelineTask(this);

	const float Duration = AnimInstance->Montage_Play(AnimMontage);
	if (Duration == 0.f)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	if (APlayerController* PC = CurrentActorInfo->PlayerController.Get())
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

	OnTimelineFloatUpdate.BindDynamic(this, &UGA_CharacterDodge::OnTimelineFloatTrackUpdate);
	OnTimelineFinished.BindDynamic(this, &UGA_CharacterDodge::OnTimelineFinished);

	TimelineTask->AddInterpFloat(DistanceCurveFloat, OnTimelineFloatUpdate);
	TimelineTask->SetTimelineFinishedFunc(OnTimelineFinished);

	TimelineTask->PlayFromStart();

	// TODO: Maybe use TimerMananger to Tick Timeline instead of TickTask
	// OwnerTaskComponent only register TickingTask in Activation NOT while TickComponent
	// So set up bTickingTask of AbilityTask before Activation to enable TickTask
	TimelineTask->ReadyForActivation();
}

void UGA_CharacterDodge::OnTimelineFloatTrackUpdate(float DistanceMultiplier)
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();

	if (!IsValid(CharacterMovement))
		return CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);

	FVector ForwardVector = Character->GetActorForwardVector();
	FVector CurrentDistance = (MoveDistance * DistanceMultiplier) * ForwardVector;

	CharacterMovement->Velocity.X = CurrentDistance.X;
	CharacterMovement->Velocity.Y = CurrentDistance.Y;
}

void UGA_CharacterDodge::OnTimelineFinished()
{
	if (APlayerController* PC = CurrentActorInfo->PlayerController.Get())
	{
		if (bIgnoreMoveInput) PC->SetIgnoreMoveInput(false);
		if (bIgnoreLookInput) PC->SetIgnoreLookInput(false);
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
