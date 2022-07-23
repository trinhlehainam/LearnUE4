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
	UAT_WaitForInteractableTarget();
	
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
	int32 bUseSourceDirectionToTrace:1;

	FTimerHandle TraceTimerHandle;
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	// Do LineTraceSingleByProfile to find Actor implementing IInteractable Interface
	void LineTraceInteractableTarget(FHitResult& OutResult, const FVector& TraceStart, const FVector& TraceEnd,
	                                 FName ProfileName,
	                                 const FCollisionQueryParams& Params);

	void AdjustTraceEndDependOnViewTarget(FVector& OutTraceEnd, const FVector& ViewStart, const FVector& ViewDir,
	                                      const FVector& TraceStart,
	                                      const FVector& TraceDir);
	void AimWithPlayerControllerViewTarget(FVector& OutTraceEnd, const FVector& TraceStart, const FVector& TraceDir);

	UFUNCTION()
	void ScanInteractabletarget();

	FGameplayAbilityTargetDataHandle MakeTargetData(const FHitResult& HitResult);
};
