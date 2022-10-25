// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CustomAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Characters/BaseCharacter.h"

void UCustomAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Owner == nullptr)
	{
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<ABaseCharacter>(PawnOwner);
	}
}

void UCustomAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (Owner == nullptr)
	{
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<ABaseCharacter>(PawnOwner);
	}

	if (!Owner.IsValid()) return;

	const FVector Velocity = Owner->GetVelocity();
	CurrentWalkSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Size();

	bIsInAir = Owner->GetMovementComponent()->IsFalling();
	bIsAccelerating = Owner->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
	bIsSprinting = Owner->IsSprinting();
	bIsJumping = Owner->IsJumping();
	bIsHoldingWeapon = Owner->IsHoldingWeapon();
	bIsAlive = Owner->IsAlive();

	AccelerateDirection = Owner->GetCharacterMovement()->GetCurrentAcceleration().GetSafeNormal();

	SprintPower = Owner->GetCurrentWalkSpeed() / Owner->GetBaseWalkSpeed();

	const FRotator ActorRotation = Owner->GetActorRotation();
	const float TargetDeltaYaw = UKismetMathLibrary::NormalizedDeltaRotator(ActorRotation, LastFrameActorRotation).Yaw
		/ DeltaTime;
	const float LerpedDeltaYaw = FMath::FInterpTo(ActorRotationDeltaYaw, TargetDeltaYaw, DeltaTime, 6.0f);
	ActorRotationDeltaYaw = FMath::Clamp(LerpedDeltaYaw, -90.f, 90.f);

	const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
	MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, ActorRotation).Yaw;

	// Only capture MovementOffsetYaw when Character is moving
	LastMovementOffsetYaw = CurrentWalkSpeed > 0.f ? MovementOffsetYaw : LastMovementOffsetYaw;
	
	LastFrameActorRotation = ActorRotation;
}

void UCustomAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	UpdateAnimationProperties(DeltaTime);
}
