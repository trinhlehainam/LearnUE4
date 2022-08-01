// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MyAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Owner == nullptr) {
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<ACharacter>(PawnOwner);
	}
}

void UMyAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (!Owner) {
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<ACharacter>(PawnOwner);
	}

	if (Owner) {
		FVector Velocity = Owner->GetVelocity();
		MovementSpeed = FVector(Velocity.X, Velocity.Y, 0.f).Size();

		bIsInAir = Owner->GetMovementComponent()->IsFalling();
		bIsAccelerating = Owner->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;

		FRotator Rotation = Owner->GetActorRotation();
		// FRotator DeltaRotation = Rotation - LastFrameRotation;	// DEBUG
		FRotator NormalizedDeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(Rotation, LastFrameRotation);
		float Target = NormalizedDeltaRotation.Yaw / DeltaTime;
		float FInterp = FMath::FInterpTo(DetalYaw, Target, DeltaTime, 6.0f);
		DetalYaw = FMath::Clamp(FInterp, -90.f, 90.f);
		LastFrameRotation = Rotation;

		// UE_LOG(LogTemp, Warning, TEXT("DeltaRotation.Yaw = %f; Target = %f"), DeltaRotation.Yaw, Target);
	}
}


void UMyAnimInstance::NativeUpdateAnimation(float DeltaTime) {
	Super::NativeUpdateAnimation(DeltaTime);

	UpdateAnimationProperties(DeltaTime);
}