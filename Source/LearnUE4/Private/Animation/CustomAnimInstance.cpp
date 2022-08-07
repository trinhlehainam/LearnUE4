// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CustomAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Characters/BaseCharacter.h"

void UCustomAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Owner == nullptr) {
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<ABaseCharacter>(PawnOwner);
	}
}

void UCustomAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (!Owner) {
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<ABaseCharacter>(PawnOwner);
	}

	if (Owner) {
		FVector Velocity = Owner->GetVelocity();
		CurrentWalkSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Size();

		bIsInAir = Owner->GetMovementComponent()->IsFalling();
		bIsAccelerating = Owner->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
		bIsSprinting = Owner->IsSprinting();

		FRotator Rotation = Owner->GetActorRotation();
		FRotator NormalizedDeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(Rotation, LastFrameRotation);
		float TargetYaw = NormalizedDeltaRotation.Yaw / DeltaTime;
		float LerpedYaw = FMath::FInterpTo(DetalYaw, TargetYaw, DeltaTime, 6.0f);
		DetalYaw = FMath::Clamp(LerpedYaw, -90.f, 90.f);
		
		LastFrameRotation = Rotation;
	}
}

void UCustomAnimInstance::NativeUpdateAnimation(float DeltaTime) {
	Super::NativeUpdateAnimation(DeltaTime);

	UpdateAnimationProperties(DeltaTime);
}