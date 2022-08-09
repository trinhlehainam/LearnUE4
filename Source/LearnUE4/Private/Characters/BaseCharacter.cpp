// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Abilities/BaseAttributeSet.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Abilities/CustomAbilitySystemComponent.h"
#include "Characters/BaseCharacterState.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionObjectType(ECC_Pawn);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
		MeshComp->SetGenerateOverlapEvents(false);
	}

	bIsSprinting = false;
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return ASC.Get();
}

float ABaseCharacter::GetCurrentHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute());
}

float ABaseCharacter::GetBaseHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetHealthAttribute());
}

float ABaseCharacter::GetBaseMaxHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetMaxHealthAttribute());
}

float ABaseCharacter::GetBaseMana() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetManaAttribute());
}

float ABaseCharacter::GetBaseMaxMana() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetMaxManaAttribute());
}

float ABaseCharacter::GetBaseStamina() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetStaminaAttribute());
}

float ABaseCharacter::GetBaseMaxStamina() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetMaxStaminaAttribute());
}

float ABaseCharacter::GetBaseWalkSpeed() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttributeBase(UBaseAttributeSet::GetWalkSpeedAttribute());
}

float ABaseCharacter::GetCurrentMaxHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxHealthAttribute());
}

float ABaseCharacter::GetCurrentMana() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetManaAttribute());
}

float ABaseCharacter::GetCurrentMaxMana() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxManaAttribute());
}

float ABaseCharacter::GetCurrentStamina() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetStaminaAttribute());
}

float ABaseCharacter::GetCurrentMaxStamina() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetMaxStaminaAttribute());
}

float ABaseCharacter::GetCurrentWalkSpeed() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC->GetNumericAttribute(UBaseAttributeSet::GetWalkSpeedAttribute());
}

void ABaseCharacter::SetInteractableTargetDataHandle(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	InteractableTargetDataHandle = TargetDataHandle;
}

FGameplayAbilityTargetDataHandle ABaseCharacter::GetInteractableTargetDataHandle() const
{
	return InteractableTargetDataHandle;
}

bool ABaseCharacter::IsSprinting() const
{
	return bIsSprinting;
}

bool ABaseCharacter::CanSprint() const
{
	return !bIsSprinting && GetCharacterMovement() && GetCharacterMovement()->IsMovingOnGround();	
}

void ABaseCharacter::Sprint()
{
	bIsSprinting = true;
}

void ABaseCharacter::StopSprinting()
{
	bIsSprinting = false;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// No binding by default because this base class for both Player and AICharacter
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!ASC.IsValid()) return;

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).AddUObject(
		this, &ABaseCharacter::OnHealthAttributeValueChange);
	
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxHealthAttribute()).AddUObject(
		this, &ABaseCharacter::OnMaxHealthAttributeValueChange);
	
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetManaAttribute()).AddUObject(
		this, &ABaseCharacter::OnManaAttributeValueChange);
	
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxManaAttribute()).AddUObject(
		this, &ABaseCharacter::OnMaxManaAttributeValueChange);
	
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStaminaAttribute()).AddUObject(
		this, &ABaseCharacter::OnStaminaAttributeValueChange);
	
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMaxStaminaAttribute()).AddUObject(
		this, &ABaseCharacter::OnMaxStaminaAttributeValueChange);
	
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetWalkSpeedAttribute()).AddUObject(
		this, &ABaseCharacter::OnWalkSpeedAttributeValueChange);
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ABaseCharacterState* PS = GetPlayerState<ABaseCharacterState>();
	if (!PS) return;
	
	ASC = Cast<UCustomAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	if (!ASC.IsValid()) return;
	
	ASC->InitAbilityActorInfo(PS, this);
	InitializeAttributes();
	GiveDefaultAbilities();
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ABaseCharacterState* PS = GetPlayerState<ABaseCharacterState>();
	if (!PS) return;
	
	ASC = Cast<UCustomAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	if (!ASC.IsValid()) return;
	
	ASC->InitAbilityActorInfo(PS, this);
	InitializeAttributes();
}

void ABaseCharacter::InitializeAttributes()
{
	if (ASC.IsValid())
	{
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(this);

		for (const TSubclassOf<UGameplayEffect>& DefaultEffect : DefaultGameplayEffects)
		{
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultEffect, 1, Context);
			if (SpecHandle.IsValid())
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ABaseCharacter::GiveDefaultAbilities()
{
	if (HasAuthority() && ASC.IsValid())
	{
		for (TSubclassOf<UBaseGameplayAbility>& DefaultAbility : DefaultAbilities)
		{
			FGameplayAbilitySpecHandle AbilityHandle = ASC->GiveAbility(FGameplayAbilitySpec(DefaultAbility, 1.0f,
				static_cast<int32>(DefaultAbility.GetDefaultObject()->AbilityInputID),
				this));

			if (DefaultAbility.GetDefaultObject()->bActivateOnGranted)
				ASC->TryActivateAbility(AbilityHandle);
		}
	}
}

void ABaseCharacter::SetHealth(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetHealthAttribute(), Value);
}

void ABaseCharacter::SetMaxHealth(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetMaxHealthAttribute(), Value);
}

void ABaseCharacter::SetMana(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetManaAttribute(), Value);
}

void ABaseCharacter::SetMaxMana(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetMaxManaAttribute(), Value);
}

void ABaseCharacter::SetStamina(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetStaminaAttribute(), Value);
}

void ABaseCharacter::SetMaxStamina(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetMaxStaminaAttribute(), Value);
}

void ABaseCharacter::SetWalkSpeed(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UBaseAttributeSet::GetWalkSpeedAttribute(), Value);
}

void ABaseCharacter::OnHealthAttributeValueChange(const FOnAttributeChangeData& NewValue)
{
	OnHealthChange.Broadcast(NewValue.NewValue);
}

void ABaseCharacter::OnMaxHealthAttributeValueChange(const FOnAttributeChangeData& NewValue)
{
	OnMaxHealthChange.Broadcast(NewValue.NewValue);
}

void ABaseCharacter::OnMaxManaAttributeValueChange(const FOnAttributeChangeData& NewValue)
{
	OnMaxManaChange.Broadcast(NewValue.NewValue);
}

void ABaseCharacter::OnMaxStaminaAttributeValueChange(const FOnAttributeChangeData& NewValue)
{
	OnMaxStaminaChange.Broadcast(NewValue.NewValue);
}

void ABaseCharacter::OnManaAttributeValueChange(const FOnAttributeChangeData& NewValue)
{
	OnManaChange.Broadcast(NewValue.NewValue);
}

void ABaseCharacter::OnStaminaAttributeValueChange(const FOnAttributeChangeData& NewValue)
{
	OnStaminaChange.Broadcast(NewValue.NewValue);
}

void ABaseCharacter::OnWalkSpeedAttributeValueChange(const FOnAttributeChangeData& NewValue)
{
	GetCharacterMovement()->MaxWalkSpeed = NewValue.NewValue;

	OnWalkSpeedChange.Broadcast(NewValue.NewValue);
}
