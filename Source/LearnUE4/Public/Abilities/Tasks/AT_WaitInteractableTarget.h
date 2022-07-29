// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/TargetingTransformType.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_WaitInteractableTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForInteractableTargetDelegate, const FGameplayAbilityTargetDataHandle&,
                                            DataHandle);

/**
 * 
 */
UCLASS()
class LEARNUE4_API UAT_WaitInteractableTarget : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAT_WaitInteractableTarget();

	UPROPERTY(BlueprintAssignable)
	FWaitForInteractableTargetDelegate OnFoundNewTarget;

	// TODO: Explain better about this case
	// Target Data Handle stores Target Data is lost at this trace 
	UPROPERTY(BlueprintAssignable)
	FWaitForInteractableTargetDelegate OnTargetLost;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks",
		meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility"))
	static UAT_WaitInteractableTarget* WaitForInteractableTarget(
		UGameplayAbility* OwningAbility,
		ECollisionChannel TraceChannel,
		EGameplayAbilityTargetingTransformType SourceTranformType,
		FName SocketName,
		float TraceRange = 200.f,
		float FireRate = 0.1f,
		bool bShowDebug = false,
		bool bUsePlayerControllerView = true,
		FName TaskInstanceName = FName("WaitForInteractableTarget")
	);

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	FGameplayAbilityTargetingLocationInfo StartLocationInfo;
	ECollisionChannel TraceChannel;
	float TraceRange;
	float FireRate;

	int8 bShowDebug:1;
	// Use Player Controller's View Transform (aka Camera) to perform additional trace to only accept Interactable Target at center of the screen
	// Only work when Actor owning this ability is controlled by Player Controller and use Line Trace
	int8 bUsePlayerControllerView:1;

	FTimerHandle TraceTimerHandle;

	// Cache TargetDataHandle from MakeTargetData method
	FGameplayAbilityTargetDataHandle TargetDataHandle;

	// Do LineTraceSingleByProfile to find Actor implementing IInteractable Interface
	void LineTraceInteractableTarget(FHitResult& OutHitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void AdjustTraceEndDependOnViewTarget(FVector& OutTraceEnd, const FVector& ViewStart, const FVector& ViewDir,
	                                      const FVector& TraceStart,
	                                      const FVector& TraceDir);

	void UsePlayerControllerViewToTrace(FHitResult& OutHitResult, const FVector& TraceStart, const FVector& TraceDir);

	using PerfromTraceFuncType = bool (UAT_WaitInteractableTarget::*)(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd, FVector& TraceDirection);
	PerfromTraceFuncType PerformLineTraceFunc;
	
	bool PerformLineTraceFromSource(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd, FVector& TraceDirection);
	
	bool PerformLineTraceFromSourceAndView(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd, FVector& TraceDirection);

	void ScanInteraction();

	FGameplayAbilityTargetDataHandle MakeTargetData(const FHitResult& HitResult);
};
