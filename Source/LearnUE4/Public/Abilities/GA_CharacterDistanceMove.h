// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "GA_CharacterDistanceMove.generated.h"

class UAT_Timeline;
class UAnimMontage;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGA_CharacterDistanceMove : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterDistanceMove();
	
protected:
	// ~ Begin UGameplayAbility Interface
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	// ~ End UGameplayAbility Interface

	UFUNCTION()
	void OnTimelineFloatTrackUpdate(float LengthMultipler);
	
	UFUNCTION()
	void OnTimelineFinished();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UAnimMontage* AnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	FName SectionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UCurveFloat* DistanceMultiplerCurveFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float BaseVelocityLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	bool bIgnoreMoveInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	bool bIgnoreLookInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	bool bUseMovementInputVectorDirection;

	FVector ForwardVector;
	
	TWeakObjectPtr<UAT_Timeline> TimelineTask;	
};
