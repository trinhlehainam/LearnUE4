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
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties(float DeltaTime);

	// Result to adjust leaning degree while running
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float DetalYaw;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	FRotator LastFrameRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float CurrentWalkSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	bool bIsAccelerating;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	bool bIsSprinting;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement)
	ABaseCharacter* Owner;
};
