// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_CharacterMontageJump.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGA_CharacterMontageJump::UGA_CharacterMontageJump()
{
}

bool UGA_CharacterMontageJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo,
                                                  const FGameplayTagContainer* SourceTags,
                                                  const FGameplayTagContainer* TargetTags,
                                                  FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());

	return IsValid(Character) && Character->CanJump();
}

void UGA_CharacterMontageJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	if (!IsValid(JumpMontage))
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();

	const float Duration = AnimInstance->Montage_Play(JumpMontage);
	AnimInstance->OnMontageEnded.AddDynamic(this, &UGA_CharacterMontageJump::OnMontageEnded);

	if (Duration == 0.f)
		return CancelAbility(Handle, ActorInfo, ActivationInfo, true);

	if (APlayerController* PC = ActorInfo->PlayerController.Get())
	{
		PC->SetIgnoreMoveInput(true);
	}
}

void UGA_CharacterMontageJump::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_CharacterMontageJump::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage != JumpMontage)
		return CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);

	UAnimInstance* AnimInstance = CurrentActorInfo->GetAnimInstance();
	ACharacter* Character = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	
	FName CurrentSection = AnimInstance->Montage_GetCurrentSection(Montage);
	if (CurrentSection == NAME_None)
		return CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);

	if (CurrentSection == AnticipationSection)
		AnimInstance->Montage_JumpToSection(BeginSection, JumpMontage);
	else if (CurrentSection == BeginSection)
	{
		if (APlayerController* PC = CurrentActorInfo->PlayerController.Get())
			PC->SetIgnoreMoveInput(false);

		Character->Jump();
	}
	else if (CurrentSection == EndSection)
	{
		Character->StopJumping();
	}
}
