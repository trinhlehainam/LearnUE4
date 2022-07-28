// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChange, float, Data);

struct FOnAttributeChangeData;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class LEARNUE4_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();

	FOnAttributeValueChange OnHealthChange;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnRep_PlayerState() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void BindASCInput();
	
	void MoveFoward(float Scale);
	void MoveRight(float Scale);

	void OnHealthAttributeValueChange(const FOnAttributeChangeData& Data);

	virtual void PawnClientRestart() override;
private:
	bool bIsAbilitiesBoundToInput;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom | Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom | Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom | Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyboardInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom | Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* GamepadInputMappingContext;
};
