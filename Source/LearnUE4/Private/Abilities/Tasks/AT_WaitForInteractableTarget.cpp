// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/AT_WaitForInteractableTarget.h"

#include "Interactable.h"

UAT_WaitForInteractableTarget* UAT_WaitForInteractableTarget::WaitForInteractableTarget(UGameplayAbility* OwningAbility,
                                                                                        FCollisionProfileName TraceProfileName, EGameplayAbilityTargetingLocationType::Type TraceLocationType,
                                                                                        FName SocketName, FName MeshComponentVariableName, FName TaskInstanceName, float TraceRange, float FireRate)
{
	UAT_WaitForInteractableTarget* TaskInstance = NewAbilityTask<UAT_WaitForInteractableTarget>(
		OwningAbility, TaskInstanceName);

	TaskInstance->TraceProfileName = TraceProfileName;
	TaskInstance->TraceRange = TraceRange;
	TaskInstance->FireRage = FireRate;

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

void UAT_WaitForInteractableTarget::LineTraceInteractableTarget(FHitResult& OutResult, FVector TraceStart,
	FVector TraceEnd, FName ProfileName, FCollisionQueryParams Params)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByProfile(HitResult, TraceStart, TraceEnd, ProfileName, Params);

	if (!HitResult.bBlockingHit) return;

	if (!HitResult.Actor->Implements<UInteractable>()) return;

	if (!IInteractable::Execute_IsAvailableForInteraction(HitResult.Actor.Get(), HitResult.Component.Get())) return;

	OutResult = HitResult;
}

FVector UAT_WaitForInteractableTarget::AdjustTraceEndDependOnViewTarget(FVector ViewStart, FVector ViewDir,
	FVector TraceStart, FVector TraceDir)
{
	FVector TraceEnd = TraceStart + (TraceDir * TraceRange);

	FVector ViewToSource = ViewStart - TraceStart;
	float ProjectionOnViewDir = FVector::DotProduct(ViewToSource, ViewDir);

	if (ProjectionOnViewDir <= 0.f) return TraceEnd;
	
	float DistanceSquared = ViewToSource.SizeSquared() - (ProjectionOnViewDir * ProjectionOnViewDir);
	float TraceRangeSquared = FMath::Square(TraceRange);
	if (DistanceSquared > TraceRangeSquared) return TraceEnd;

	float ExtendRange = FMath::Sqrt(TraceRangeSquared - DistanceSquared);
	float NewRange = ProjectionOnViewDir + ExtendRange;

	return ViewStart + (ViewDir * NewRange);
}

void UAT_WaitForInteractableTarget::ScanInteractabletarget()
{
	// TODO: Set up default TraceStart and TraceEnd
	// TODO: Modify TraceEnd if this Actor controlled by PlayerController
	// TODO: Output Result
	
	if (!Ability) return;

	// Transform of Source Object (can be an Actor, or UMeshComponent) used to trace
	FTransform SourceTransform = StartLocationInfo.GetTargetingTransform();
	FVector TraceStart = SourceTransform.GetLocation();
	FRotator TraceRotation = SourceTransform.GetRotation().Rotator();
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	// If this Actor is controlled by User Player, perform trace from Player Controller's View Point (Camera in most case)
	if (PC)
	{
		PC->GetPlayerViewPoint(TraceStart, TraceRotation);
	}

	// Convert Rotator to Direction Unit Vector
	FVector TraceDir = TraceRotation.Vector();
	FVector TraceEnd = TraceStart + (TraceDir * TraceRange);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(StartLocationInfo.SourceActor);

	FHitResult HitResult;
	LineTraceInteractableTarget(HitResult, TraceStart, TraceEnd, TraceProfileName.Name, Params);
	
}

FGameplayAbilityTargetDataHandle UAT_WaitForInteractableTarget::MakeTargetData(const FHitResult& HitResult)
{
	return StartLocationInfo.MakeTargetDataHandleFromHitResult(Ability, HitResult);
}
