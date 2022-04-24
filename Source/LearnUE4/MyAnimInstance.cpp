// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (!Owner) {
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<AMyCharacter>(PawnOwner);
	}
}

void UMyAnimInstance::UpdateAnimationProperties()
{
	if (!Owner) {
		APawn* PawnOwner = TryGetPawnOwner();
		Owner = Cast<AMyCharacter>(PawnOwner);
	}

	if (Owner) {
		FVector Speed = Owner->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Owner->GetMovementComponent()->IsFalling();
		bIsAccelerating = Owner->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	}
}
