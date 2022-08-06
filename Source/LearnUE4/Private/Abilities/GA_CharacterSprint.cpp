// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_CharacterSprint.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGA_CharacterSprint::UGA_CharacterSprint()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	WalkSpeedMultiplier = 1.f;
	CrouchSpeedMultiplier = 1.f;
}

bool UGA_CharacterSprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayTagContainer* SourceTags,
                                             const FGameplayTagContainer* TargetTags,
                                             FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
		return false;

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();

	if (!IsValid(Character) || !IsValid(CharacterMovement))
		return false;
	
	return CharacterMovement->IsMovingOnGround();
}

void UGA_CharacterSprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			return;
		}

		ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
		UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();

		InitialMaxWalkSpeed = CharacterMovement->MaxWalkSpeed;
		InitialMaxCrouchSpeed = CharacterMovement->MaxWalkSpeedCrouched;
		
		CharacterMovement->MaxWalkSpeed = CharacterMovement->MaxWalkSpeed * WalkSpeedMultiplier;
		CharacterMovement->MaxWalkSpeedCrouched = CharacterMovement->MaxCustomMovementSpeed * CrouchSpeedMultiplier;
	}
}

void UGA_CharacterSprint::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo,
                                     bool bReplicateEndAbility, bool bWasCancelled)
{
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();

	CharacterMovement->MaxWalkSpeed = InitialMaxWalkSpeed;
	CharacterMovement->MaxWalkSpeedCrouched = InitialMaxCrouchSpeed;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_CharacterSprint::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo)
{
	CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}
