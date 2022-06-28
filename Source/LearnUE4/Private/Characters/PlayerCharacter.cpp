// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/AttributeSet_BaseAttributes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Camera/CameraComponent.h"
#include "Characters/PlayerState_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LearnUE4/Common/AbilityInputID.h"

APlayerCharacter::APlayerCharacter()
{
	bIsAbilitiesBoundToInput = false;

	// Don't let Controller rotating Character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Let Character Movement Component rotate Character toward movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));

	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera->bUsePawnControlRotation = false;

	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!ASC.IsValid()) return;
	ASC->GetGameplayAttributeValueChangeDelegate(UAttributeSet_BaseAttributes::GetHealthAttribute()).AddUObject(
		this, &APlayerCharacter::OnHealthAttributeValueChange);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerState_Player* PS = GetPlayerState<APlayerState_Player>();
	if (!PS) return;
	ASC = PS->GetAbilitySystemComponent();

	if (!ASC.IsValid()) return;
	ASC->InitAbilityActorInfo(PS, this);
	InitializeAttributes();
	GiveDefaultAbilities();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	APlayerState_Player* PS = GetPlayerState<APlayerState_Player>();
	if (!PS) return;
	ASC = PS->GetAbilitySystemComponent();

	if (!ASC.IsValid()) return;
	ASC->InitAbilityActorInfo(PS, this);
	InitializeAttributes();
	BindASCInput();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	BindASCInput();
}

void APlayerCharacter::BindASCInput()
{
	if (InputComponent && ASC.IsValid() && !bIsAbilitiesBoundToInput)
	{
		FGameplayAbilityInputBinds BindInfo("Confirm", "Cancel", "EAbilityInputID",
		                                    static_cast<int32>(EAbilityInputID::Confirm),
		                                    static_cast<int32>(EAbilityInputID::Cancel));
		ASC->BindAbilityActivationToInputComponent(InputComponent, BindInfo);
		bIsAbilitiesBoundToInput = true;
	}
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

void APlayerCharacter::OnHealthAttributeValueChange(const FOnAttributeChangeData& Data)
{
	OnHealthChange.Broadcast(Data.NewValue);
}
