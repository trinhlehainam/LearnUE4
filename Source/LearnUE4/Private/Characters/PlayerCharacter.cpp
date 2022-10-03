// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Input/CustomEnhancedInputComponent.h"
#include "Abilities/AbilityInputID.h"
#include "Abilities/CustomAbilitySystemComponent.h"
#include "Abilities/CustomGameplayTags.h"
#include "Characters/CustomMovementComponent.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Don't let Controller rotating Character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	bIsAbilitiesBoundToInput = false;

	AIControllerClass = nullptr;

	MoveComp = Cast<UCustomMovementComponent>(GetCharacterMovement());
	// Let Character Movement Component rotate Character toward movement direction
	if (MoveComp)
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	}

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));

	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera->bUsePawnControlRotation = false;

	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bIsHoldingWeapon = false;
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	BindGameplayAbilitiesToInputComponent(InputComponent);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	if (UCustomEnhancedInputComponent* EnhancedInputComponent = Cast<UCustomEnhancedInputComponent>(
		PlayerInputComponent))
	{
		EnhancedInputComponent->BindActionByInputTag(
			InputConfig, ECustomGameplayTags::InputTag_Move,
			ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Move);

		EnhancedInputComponent->BindActionByInputTag(
			InputConfig, ECustomGameplayTags::InputTag_Look,
			ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Look);
	}

	BindGameplayAbilitiesToInputComponent(PlayerInputComponent);
}

void APlayerCharacter::BindGameplayAbilitiesToInputComponent(UInputComponent* PlayerInputComponent)
{
	UCustomEnhancedInputComponent* EnhancedInputComponent = Cast<UCustomEnhancedInputComponent>(PlayerInputComponent);

	if (bIsAbilitiesBoundToInput || !IsValid(EnhancedInputComponent) || !ASC.IsValid() || !IsValid(InputConfig)) return;

	FGameplayAbilityInputBinds BindInfo("Confirm", "Cancel", "EAbilityInputID",
	                                    static_cast<int32>(EAbilityInputID::Confirm),
	                                    static_cast<int32>(EAbilityInputID::Cancel));
	ASC->BindAbilityActivationToInputComponent(PlayerInputComponent, BindInfo);

	for (const FGameplayTagInputAction& Input : InputConfig->TagInputs)
	{
		if (!IsValid(Input.InputAction)) continue;

		EAbilityInputID AbilityInputID = Input.AbilityInputID;

		if (AbilityInputID == EAbilityInputID::None || AbilityInputID == EAbilityInputID::Confirm || AbilityInputID
			== EAbilityInputID::Cancel)
			continue;

		EnhancedInputComponent->BindGameplayAbilityInput(ASC.Get(), static_cast<int32>(AbilityInputID),
		                                                 Input.InputAction);
	}

	bIsAbilitiesBoundToInput = true;
}

void APlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	if (!IsValid(Controller)) return;

	FVector2D Axis2D = InputActionValue.Get<FVector2D>();

	if (Axis2D.X != 0.f)
		MoveRight(Axis2D.X);

	if (Axis2D.Y != 0.f)
		MoveFoward(Axis2D.Y);
}

void APlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	if (!IsValid(Controller)) return;

	FVector2D LookValue = InputActionValue.Get<FVector2D>();

	if (LookValue.X != 0.f)
		AddControllerYawInput(LookValue.X);

	if (LookValue.Y != 0.f)
		AddControllerPitchInput(LookValue.Y);
}

void APlayerCharacter::MoveFoward(float Scale)
{
	if ((Controller != NULL) && (Scale != 0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Scale);
	}
}

void APlayerCharacter::MoveRight(float Scale)
{
	if ((Controller != NULL) && (Scale != 0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Scale);
	}
}

void APlayerCharacter::PawnClientRestart()
{
	// Make sure that we have a valid PlayerController.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			// We don't want to clear all Input Mapping Contexts because PlayerController has its own Input Mapping Contexts to navigate UI|HUD
			Subsystem->RemoveMappingContext(KeyboardInputMappingContext);
			Subsystem->RemoveMappingContext(GamepadInputMappingContext);

			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(KeyboardInputMappingContext, 0);
			Subsystem->AddMappingContext(GamepadInputMappingContext, 0);
		}
	}

	// SetupPlayerInputComponent is called inside here
	Super::PawnClientRestart();
}
