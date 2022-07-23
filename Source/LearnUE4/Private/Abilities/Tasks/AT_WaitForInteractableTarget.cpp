// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/AT_WaitForInteractableTarget.h"

#include "Interactable.h"

UAT_WaitForInteractableTarget::UAT_WaitForInteractableTarget()
{
}

UAT_WaitForInteractableTarget* UAT_WaitForInteractableTarget::WaitForInteractableTarget(UGameplayAbility* OwningAbility,
	FCollisionProfileName TraceProfileName, EGameplayAbilityTargetingLocationType::Type TraceLocationType,
	FName SocketName, FName MeshComponentVariableName, FName TaskInstanceName, float TraceRange, float FireRate)
{
	UAT_WaitForInteractableTarget* TaskInstance = NewAbilityTask<UAT_WaitForInteractableTarget>(
		OwningAbility, TaskInstanceName);

	TaskInstance->TraceProfileName = TraceProfileName;
	TaskInstance->TraceRange = TraceRange;
	TaskInstance->FireRage = FireRate;

	// TODO: Adjust this value depend on Trace Location Type
	TaskInstance->bUseSourceDirectionToTrace = false;

	AActor* SourceActor = OwningAbility->GetCurrentActorInfo()->AvatarActor.Get();

	// Find Mesh Component has variable name same as MeshComponentVariableName
	TArray<UMeshComponent*> MeshComps;
	SourceActor->GetComponents<UMeshComponent>(MeshComps, true);
	UMeshComponent* SourceComponent = nullptr;
	for (UMeshComponent* MeshComp : MeshComps)
	{
		if (MeshComp->GetFName().Compare(MeshComponentVariableName) == 0)
		{
			SourceComponent = MeshComp;
			break;
		}
	}
	//

	check(SourceComponent);

	TaskInstance->StartLocationInfo.SourceActor = SourceActor;
	TaskInstance->StartLocationInfo.LocationType = TraceLocationType;
	TaskInstance->StartLocationInfo.SourceComponent = SourceComponent;
	TaskInstance->StartLocationInfo.SourceSocketName = SocketName;
	TaskInstance->StartLocationInfo.SourceAbility = OwningAbility;

	return TaskInstance;
}

void UAT_WaitForInteractableTarget::Activate()
{
	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this,
	                                       &UAT_WaitForInteractableTarget::ScanInteractabletarget, true);
}

void UAT_WaitForInteractableTarget::OnDestroy(bool bInOwnerFinished)
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_WaitForInteractableTarget::LineTraceInteractableTarget(FHitResult& OutResult, const FVector& TraceStart,
                                                                const FVector& TraceEnd, FName ProfileName,
                                                                const FCollisionQueryParams& Params)
{
	// Only accept hit result when Line Trace found valid Interactable Target
	OutResult.bBlockingHit = false;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByProfile(HitResult, TraceStart, TraceEnd, ProfileName, Params);

	if (!HitResult.bBlockingHit) return;

	if (!HitResult.Actor->Implements<UInteractable>()) return;

	if (!IInteractable::Execute_IsAvailableForInteraction(HitResult.Actor.Get(), HitResult.Component.Get())) return;

	OutResult = HitResult;
}

void UAT_WaitForInteractableTarget::AdjustTraceEndDependOnViewTarget(FVector& OutTraceEnd, const FVector& ViewStart,
                                                                     const FVector& ViewDir, const FVector& TraceStart,
                                                                     const FVector& TraceDir)
{
	OutTraceEnd = TraceStart + (TraceDir * TraceRange);

	FVector ViewToSource = ViewStart - TraceStart;
	float ProjectionOnViewDir = FVector::DotProduct(ViewToSource, ViewDir);

	// Reject case when ViewPoint is at or in front of Source Trace
	if (ProjectionOnViewDir <= 0.f) return;

	float AltitudeSquare = ViewToSource.SizeSquared() - FMath::Square(ProjectionOnViewDir);
	float TraceRangeSquared = FMath::Square(TraceRange);
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
	LineTraceInteractableTarget(HitResult, ViewStart, ViewEnd, TraceProfileName.Name, Params);
	
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
	LineTraceInteractableTarget(HitResult, TraceStart, TraceEnd, TraceProfileName.Name, Params);

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
		if (TargetDataHandle.Num() > 0)
		{
			AActor* InteractableTarget = TargetDataHandle.Get(0)->GetHitResult()->GetActor();
			if (HitResult.GetActor() != InteractableTarget)
			{
				OnTargetLost.Broadcast(TargetDataHandle);
				MakeTargetData(HitResult);
				OnFoundNewTarget.Broadcast(TargetDataHandle);
			}
		}
		else
		{
			MakeTargetData(HitResult);
			OnFoundNewTarget.Broadcast(TargetDataHandle);
		}
	}
	
}

FGameplayAbilityTargetDataHandle UAT_WaitForInteractableTarget::MakeTargetData(const FHitResult& HitResult)
{
	return StartLocationInfo.MakeTargetDataHandleFromHitResult(Ability, HitResult);
}
