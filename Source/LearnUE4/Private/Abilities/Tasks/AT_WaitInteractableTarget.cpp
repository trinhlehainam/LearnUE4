// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/AT_WaitInteractableTarget.h"

#include "AbilitySystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Objects/Interactable.h"
#include "GameFramework/Character.h"

UAT_WaitInteractableTarget::UAT_WaitInteractableTarget()
{
}

UAT_WaitInteractableTarget* UAT_WaitInteractableTarget::WaitForInteractableTarget(UGameplayAbility* OwningAbility,
	ECollisionChannel TraceChannel, EGameplayAbilityTargetingTransformType SourceTranformType, FName SocketName,
	float TraceRange, float FireRate, bool bShowDebug, bool bUsePlayerControllerView, FName TaskInstanceName)
{
	UAT_WaitInteractableTarget* TaskInstance = NewAbilityTask<UAT_WaitInteractableTarget>(
		OwningAbility, TaskInstanceName);

	TaskInstance->TraceChannel = TraceChannel;
	TaskInstance->TraceRange = TraceRange;
	TaskInstance->FireRate = FireRate;
	TaskInstance->bShowDebug = bShowDebug;

	// TODO: Handle to use PlayerController's View (aka Camera) Trace to produce final result
	TaskInstance->PerformLineTraceFunc = bUsePlayerControllerView
		                                 ? &UAT_WaitInteractableTarget::PerformLineTraceFromSourceAndView
		                                 : &UAT_WaitInteractableTarget::PerformLineTraceFromSource;

	AActor* SourceActor = OwningAbility->GetCurrentActorInfo()->AvatarActor.Get();
	UMeshComponent* SourceComponent = nullptr;

	EGameplayAbilityTargetingLocationType::Type LocationType;

	// TODO: Depend on Targeting Transform Type, process to find appropriate SourceComponent
	if (SourceTranformType == EGameplayAbilityTargetingTransformType::ActorTransform)
	{
		LocationType = EGameplayAbilityTargetingLocationType::ActorTransform;
	}
	else
	{
		// Only support using socket of Skeleton Mesh Component in ACharacter for now
		LocationType = EGameplayAbilityTargetingLocationType::SocketTransform;
		if (ACharacter* Character = Cast<ACharacter>(SourceActor))
		{
			SourceComponent = Character->GetMesh();
		}
		check(SourceComponent);
	}

	TaskInstance->StartLocationInfo.SourceActor = SourceActor;
	TaskInstance->StartLocationInfo.LocationType = LocationType;
	TaskInstance->StartLocationInfo.SourceComponent = SourceComponent;
	TaskInstance->StartLocationInfo.SourceSocketName = SocketName;
	TaskInstance->StartLocationInfo.SourceAbility = OwningAbility;

	return TaskInstance;
}

void UAT_WaitInteractableTarget::Activate()
{
	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle,
	                                       this, &UAT_WaitInteractableTarget::ScanInteraction,
	                                       FireRate, true);
}

void UAT_WaitInteractableTarget::OnDestroy(bool bInOwnerFinished)
{
	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);
	OnTargetLost.Clear();
	OnFoundNewTarget.Clear();

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_WaitInteractableTarget::LineTraceInteractableTarget(FHitResult& OutHitResult, const FVector& TraceStart,
                                                             const FVector& TraceEnd)
{
	// Only accept hit result when Line Trace found valid Interactable Target
	OutHitResult.bBlockingHit = false;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(StartLocationInfo.SourceActor);
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, TraceChannel, QueryParams);

	// TODO: Use Collision Response

	if (!HitResult.bBlockingHit) return;

	if (!HitResult.Actor->Implements<UInteractable>()) return;

	if (!IInteractable::Execute_IsAvailableForInteraction(HitResult.GetActor(), HitResult.GetComponent())) return;

	FGameplayTagContainer TagContainer;
	AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
	if (!IInteractable::Execute_HasRequiredGameplayTags(HitResult.GetActor(), TagContainer)) return;

	OutHitResult = HitResult;
}

void UAT_WaitInteractableTarget::AdjustTraceEndDependOnViewTarget(FVector& OutTraceEnd, const FVector& ViewStart,
                                                                  const FVector& ViewDir, const FVector& TraceStart,
                                                                  const FVector& TraceDir)
{
	FVector ViewToSource = TraceStart - ViewStart;
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

void UAT_WaitInteractableTarget::UsePlayerControllerViewToTrace(FHitResult& OutHitResult, const FVector& TraceStart,
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

	LineTraceInteractableTarget(OutHitResult, ViewStart, ViewEnd);

	// Because Hit Result doesn't save TraceEnd value when there Trace doesn't Hit
	// So Cache ViewEnd to Hit Result's TraceEnd
	OutHitResult.TraceEnd = ViewEnd;
	if (!OutHitResult.bBlockingHit) return;

	// Use Hit Location as Trace End result when Hit Location inside Source Trace Range
	bool bUseHitLocation = FVector::DistSquared(OutHitResult.Location, TraceStart) <= FMath::Square(TraceRange);
	if (!bUseHitLocation) return;

	// TODO: Write document
	// Hit Location sometimes may not at Surface of Component's Material, 
	// We want to offset Hit Location inside Component a bit for next Line Trace
	float OffsetScale = 0.01f;
	FVector HitLocationOffset = OutHitResult.Location + (ViewDir * OffsetScale);
	//

	OutHitResult.TraceEnd = HitLocationOffset;
}

bool UAT_WaitInteractableTarget::PerformLineTraceFromSource(FHitResult& HitResult, FVector& TraceStart,
                                                            FVector& TraceEnd, FVector& TraceDirection)
{
	// Hit Result Trace from Source Location
	FHitResult SourceHitResult;
	LineTraceInteractableTarget(SourceHitResult, TraceStart, TraceEnd);

	HitResult = SourceHitResult;

	return HitResult.bBlockingHit;
}

bool UAT_WaitInteractableTarget::PerformLineTraceFromSourceAndView(FHitResult& HitResult, FVector& TraceStart,
                                                                   FVector& TraceEnd, FVector& TraceDirection)
{
	// Hit Result Trace from PlayerController's View
	FHitResult ViewHitResult;
	UsePlayerControllerViewToTrace(ViewHitResult, TraceStart, TraceDirection);

	TraceEnd = ViewHitResult.TraceEnd;

	// Hit Result Trace from Source Location
	FHitResult SourceHitResult;
	LineTraceInteractableTarget(SourceHitResult, TraceStart, TraceEnd);

	bool bFoundTarget = false;
	// TODO: Write document
	// There are POSSIBLE cases when use both Source Transform and PlayerController's View Transform to trace
	// - Source Trace Hits different Target Actor
	// - Source Trace Hits different Component part of Target Actor
	if (ViewHitResult.bBlockingHit && SourceHitResult.bBlockingHit)
	{
		bFoundTarget = ViewHitResult.Actor == SourceHitResult.Actor &&
			ViewHitResult.Component == SourceHitResult.Component;
	}

	HitResult = SourceHitResult;

	return bFoundTarget;
}

void UAT_WaitInteractableTarget::ScanInteraction()
{
	if (!Ability) return;

	// Transform of Source Object (can be an Actor, or UMeshComponent) used to trace
	FTransform SourceTransform = StartLocationInfo.GetTargetingTransform();
	FVector TraceStart = SourceTransform.GetLocation();
	FVector TraceDir = SourceTransform.GetRotation().Rotator().Vector();
	FVector TraceEnd = TraceStart + (TraceDir * TraceRange);

	FHitResult HitResult;
	bool bTargetFound = (this->*PerformLineTraceFunc)(HitResult, TraceStart, TraceEnd, TraceDir);

	if (!bTargetFound)
	{
		if (TargetDataHandle.Num() > 0 && TargetDataHandle.Get(0)->GetHitResult()->GetActor())
		{
			OnTargetLost.Broadcast(TargetDataHandle);
		}

		// TODO: Write document
		// Even bFoundTarget is false, SourceHitResult can still be hit
		// We need to adjust SourceHitResult before MakeTargetData
		HitResult.Init(TraceStart, TraceEnd);
		//

		TargetDataHandle = MakeTargetData(HitResult);
	}
	else
	{
		TraceEnd = HitResult.Location;
		bool bNotifyFoundNewTarget = true;

		if (TargetDataHandle.Num() > 0)
		{
			bNotifyFoundNewTarget = false;
			AActor* OldInteractableTarget = TargetDataHandle.Get(0)->GetHitResult()->GetActor();

			if (HitResult.GetActor() != OldInteractableTarget)
			{
				bNotifyFoundNewTarget = true;
				OnTargetLost.Broadcast(TargetDataHandle);
			}
		}

		if (bNotifyFoundNewTarget)
		{
			TargetDataHandle = MakeTargetData(HitResult);
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

FGameplayAbilityTargetDataHandle UAT_WaitInteractableTarget::MakeTargetData(const FHitResult& HitResult)
{
	return StartLocationInfo.MakeTargetDataHandleFromHitResult(Ability, HitResult);
}