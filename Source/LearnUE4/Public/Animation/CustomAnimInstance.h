// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CustomAnimInstance.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS()
class LEARNUE4_API UCustomAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties(float DeltaTime);

	// Result to adjust leaning degree while running
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float ActorRotationDeltaYaw;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	FRotator LastFrameActorRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	FVector AccelerateDirection;

	// Offset Yaw from Movement Direction and Controller Forward Direction
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float MovementOffsetYaw;	

	// Capture Movement Offset Yaw when the last time Character was moved
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float LastMovementOffsetYaw;	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float CurrentWalkSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character)
	bool bIsAlive;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	bool bIsAccelerating;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	bool bIsSprinting;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	bool bIsJumping;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float SprintPower;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	bool bIsHoldingWeapon;
	
	TWeakObjectPtr<ABaseCharacter> Owner;
};
