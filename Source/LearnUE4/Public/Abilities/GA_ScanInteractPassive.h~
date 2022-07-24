// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "GA_ScanInteractPassive.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UGA_ScanInteractPassive : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_ScanInteractPassive();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Ability|Interaction")
	void OnFoundNewTarget(const FGameplayAbilityTargetDataHandle& DataHandle);
	void OnFoundNewTarget_Implementation(const FGameplayAbilityTargetDataHandle& DataHandle);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Ability|Interaction")
	void OnTargetLost(const FGameplayAbilityTargetDataHandle& DataHandle);
	void OnTargetLost_Implementation(const FGameplayAbilityTargetDataHandle& DataHandle);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	TEnumAsByte<EGameplayAbilityTargetingLocationType::Type> TraceLocationType;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	FName SocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	FName MeshComponentVariableName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float TraceRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float FireRate;

};
