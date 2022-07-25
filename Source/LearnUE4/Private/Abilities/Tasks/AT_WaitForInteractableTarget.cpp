// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/AT_WaitForInteractableTarget.h"

#include "DrawDebugHelpers.h"
#include "Interactable.h"

UAT_WaitForInteractableTarget::UAT_WaitForInteractableTarget()
{
}

UAT_WaitForInteractableTarget* UAT_WaitForInteractableTarget::WaitForInteractableTarget(UGameplayAbility* OwningAbility,
	ECollisionChannel TraceChannel, EGameplayAbilityTargetingLocationType::Type TraceLocationType, FName SocketName,
	FName MeshComponentVariableName, float TraceRange, float FireRate, bool bShowDebug, FName TaskInstanceName)
{
	UAT_WaitForInteractableTarget* TaskInstance = NewAbilityTask<UAT_WaitForInteractableTarget>(
		OwningAbility, TaskInstanceName);

	TaskInstance->TraceChannel = TraceChannel;
	TaskInstance->TraceRange = TraceRange;
	TaskInstance->FireRate = FireRate;
	TaskInstance->bShowDebug = bShowDebug;

	// TODO: Adjust this value depend on Trace Location Type
	TaskInstance->bUseSourceDirectionToTrace = false;

	AActor* SourceActor = OwningAbility->GetCurrentActorInfo()->AvatarActor.Get();

	// TODO: Depend on Trace Location Type, Source Component doesn't need to be queried
	// Find Mesh Component has variable name same as MeshComponentVariableName
	// UMeshComponent* SourceComponent = Cast<USkeletalMeshComponent>(SourceActor->GetDefaultSubobjectByName(MeshComponentVariableName));
	// check(SourceComponent);
	//


	TaskInstance->StartLocationInfo.SourceActor = SourceActor;
	TaskInstance->StartLocationInfo.LocationType = TraceLocationType;
	// TaskInstance->StartLocationInfo.SourceComponent = SourceComponent;
	TaskInstance->StartLocationInfo.SourceSocketName = SocketName;
	TaskInstance->StartLocationInfo.SourceAbility = OwningAbility;

	return TaskInstance;
}

void UAT_WaitForInteractableTarget::Activate()
{
	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle,
	                                       this, &UAT_WaitForInteractableTarget::ScanInteractabletarget,
	                                       FireRate, true);
}

void UAT_WaitForInteractableTarget::OnDestroy(bool bInOwnerFinished)
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);
	OnTargetLost.Clear();
	OnFoundNewTarget.Clear();

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_WaitForInteractableTarget::LineTraceInteractableTarget(FHitResult& OutResult, const FVector& TraceStart,
                                                                const FVector& TraceEnd,
                                                                const FCollisionQueryParams& Params)
{
	// Only accept hit result when Line Trace found valid Interactable Target
	OutResult.bBlockingHit = false;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, TraceChannel, Params);

	if (!HitResult.bBlockingHit) return;

	// Only accept collision overlap to Trace Channel
	if (HitResult.Component.Get()->GetCollisionResponseToChannel(TraceChannel) != ECR_Overlap) return;

	if (!HitResult.Actor->Implements<UInteractable>()) return;

	if (!IInteractable::Execute_IsAvailableForInteraction(HitResult.Actor.Get(), HitResult.Component.Get())) return;

	OutResult = HitResult;
}

void UAT_WaitForInteractableTarget::AdjustTraceEndDependOnViewTarget(FVector& OutTraceEnd, const FVector& ViewStart,
                                                                     const FVector& ViewDir, const FVector& TraceStart,
                                                                     const FVector& TraceDir)
{
	FVector ViewToSource = ViewStart - TraceStart;
	float ProjectionOnViewDir = FVector::DotProduct(ViewToSource, ViewDir);

	// Reject case when ViewPoint is at or in front of Source Trace
	// WARN: This also reject the case when View (Camera) is at behind Character, and View Direction goes through Character
	if (ProjectionOnViewDir <= 0.f) return;

	float AltitudeSquare = ViewToSource.SizeSquared() - FMath::Square(ProjectionOnViewDir);
	float TraceRangeSquared = FMath::Square(TraceRange);

	// Reject case when Distance from Source Trace to View Direction larger than Trace Range
	if (AltitudeSquare > TraceRangeSquared) return;

	float ExtendedRange = FMath::Sqrt(TraceRangeSquared - AltitudeSquare);
	float NewRange = ProjectionOnViewDir + ExtendedRange;

	OutTraceEnd = ViewStart + (ViewDir * NewRange);
}

void UAT_WaitForInteractableTarget::AimWithPlayerControllerViewTarget(FVector& OutTraceEnd, const FVector& TraceStart,
                                                                      const FVector& TraceDir)
{
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (!PC) return;

	// If this Actor is controlled by User Player, perform trace from Player Controller's View Point (Camera in most case)
	FVector ViewStart;
	FRotator ViewRotation;
	PC->GetPlayerViewPoint(ViewStart, ViewRotation);

	FVector ViewDir = ViewRotation.Vector();
	FVector ViewEnd = ViewStart + (ViewDir * TraceRange);
	AdjustTraceEndDependOnViewTarget(ViewEnd, ViewStart, ViewDir, TraceStart, TraceDir);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(StartLocationInfo.SourceActor);
	LineTraceInteractableTarget(HitResult, ViewStart, ViewEnd, Params);

	if (!HitResult.bBlockingHit) return;

	// Use Hit Location as Trace End result when Hit Location inside Source Trace Range
	bool bUseHitLocation = (HitResult.Location - TraceStart).SizeSquared() <= FMath::Square(TraceRange);

	OutTraceEnd = bUseHitLocation ? HitResult.Location : ViewEnd;
}

void UAT_WaitForInteractableTarget::ScanInteractabletarget()
{
	if (!Ability) return;

	// Transform of Source Object (can be an Actor, or UMeshComponent) used to trace
	FTransform SourceTransform = StartLocationInfo.GetTargetingTransform();
	FVector TraceStart = SourceTransform.GetLocation();
	FVector TraceDir = SourceTransform.GetRotation().Rotator().Vector();
	FVector TraceEnd = TraceStart + (TraceDir * TraceRange);

	AimWithPlayerControllerViewTarget(TraceEnd, TraceStart, TraceDir);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(StartLocationInfo.SourceActor);
	LineTraceInteractableTarget(HitResult, TraceStart, TraceEnd, Params);

	if (!HitResult.bBlockingHit)
	{
		if (TargetDataHandle.Num() > 0 && TargetDataHandle.Get(0)->GetHitResult()->GetActor())
		{
			OnTargetLost.Broadcast(TargetDataHandle);
		}

		HitResult.Location = TraceEnd;
		MakeTargetData(HitResult);
	}
	else
	{
		bool bNotifyFoundNewTarget = true;
		if (TargetDataHandle.Num() > 0)
		{
			bNotifyFoundNewTarget = false;
			AActor* InteractableTarget = TargetDataHandle.Get(0)->GetHitResult()->GetActor();

			if (HitResult.GetActor() != InteractableTarget)
			{
				bNotifyFoundNewTarget = true;
				OnTargetLost.Broadcast(TargetDataHandle);
			}
		}

		if (bNotifyFoundNewTarget)
		{
			MakeTargetData(HitResult);
			OnFoundNewTarget.Broadcast(TargetDataHandle);
		}
	}

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	if (bShowDebug)
	{
		FColor DebugSphereColor = HitResult.bBlockingHit ? FColor::Red : FColor::Green;
		// Line Trace
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, FireRate, 0, 1.f);
		// Visual Trace End Point with Sphere
		DrawDebugSphere(GetWorld(), TraceEnd, 5.f, 32, DebugSphereColor, false, FireRate, 0, 1.f);
		// Trace Range
		DrawDebugSphere(GetWorld(), TraceStart, TraceRange, 32, FColor::Green, false, FireRate, 0, 1.f);
	}
#endif
}

FGameplayAbilityTargetDataHandle UAT_WaitForInteractableTarget::MakeTargetData(const FHitResult& HitResult)
{
	return StartLocationInfo.MakeTargetDataHandleFromHitResult(Ability, HitResult);
}
