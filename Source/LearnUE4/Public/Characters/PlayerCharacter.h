// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

struct FOnAttributeChangeData;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
struct FInputActionValue;
class UInputConfig;
class UCustomMovementComponent;

/**
 * 
 */
UCLASS()
class LEARNUE4_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	void MoveFoward(float Scale);

	void MoveRight(float Scale);

protected:
	virtual void OnRep_PlayerState() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void BindGameplayAbilitiesToInputComponent(UInputComponent* PlayerInputComponent);

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	virtual void PawnClientRestart() override;
	
	int8 bIsAbilitiesBoundToInput:1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom | Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom | Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom | Input", meta = (AllowPrivateAccess = "true"))
	UInputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom | Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyboardInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom | Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* GamepadInputMappingContext;

	UPROPERTY()
	UCustomMovementComponent* MoveComp;
};
