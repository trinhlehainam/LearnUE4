// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_WaitForInteractableTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForInteractableTargetDelegate, const FGameplayAbilityTargetDataHandle&,
                                            DataHandle);

/**
 * 
 */
UCLASS()
class LEARNUE4_API UAT_WaitForInteractableTarget : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWaitForInteractableTargetDelegate OnFoundNewTarget;

	UPROPERTY(BlueprintAssignable)
	FWaitForInteractableTargetDelegate OnTargetLost;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility"))
	static UAT_WaitForInteractableTarget* WaitForInteractableTarget(
		UGameplayAbility* OwningAbility,
		FCollisionProfileName TraceProfileName,
		EGameplayAbilityTargetingLocationType::Type TraceLocationType,
		FName SocketName,
		FName MeshComponentVariableName = FName("Mesh"),
		FName TaskInstanceName = FName("WaitForInteractableTarget"),
		float TraceRange = 200.f,
		float FireRate = 0.1f
	);

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	FGameplayAbilityTargetingLocationInfo StartLocationInfo;
	FCollisionProfileName TraceProfileName;
	float TraceRange;
	float FireRage;

	FTimerHandle TraceTimerHandle;

	// Do LineTraceSingleByProfile to find Actor implementing IInteractable Interface
	void LineTraceInteractableTarget(FHitResult& OutResult, FVector TraceStart, FVector TraceEnd, FName ProfileName, FCollisionQueryParams Params);

	FVector AdjustTraceEndDependOnViewTarget(FVector ViewStart, FVector ViewRotation, FVector TraceStart, FVector TraceDir);

	UFUNCTION()
	void ScanInteractabletarget();

	FGameplayAbilityTargetDataHandle MakeTargetData(const FHitResult& HitResult);
};
