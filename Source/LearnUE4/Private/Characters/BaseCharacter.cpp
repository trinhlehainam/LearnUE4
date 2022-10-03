// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Abilities/BaseAttributeSet.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Abilities/CustomAbilitySystemComponent.h"
#include "Characters/BaseCharacterState.h"
#include "Components/CapsuleComponent.h"
#include "Objects/WeaponActor.h"

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
		MeshComp->SetGenerateOverlapEvents(false);
	}

	bIsSprinting = false;
	bIsAlive = false;
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

void ABaseCharacter::CollectWeapon(AWeaponActor* WeaponActor)
{
	WeaponActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	                               FName("UnequipWeaponSocket"));

	Weapon = WeaponActor;
}

AWeaponActor* ABaseCharacter::GetCurrentWeapon() const
{
	return Weapon;
}

bool ABaseCharacter::IsHoldingWeapon() const
{
	if (!IsValid(Weapon)) return false;

	FName AttachingSocket = Weapon->GetAttachParentSocketName();

	if (AttachingSocket == FName("AxeSocket"))
		return true;

	return false;
}

bool ABaseCharacter::IsAlive() const
{
	return GetBaseHealth() > 0.f;
}

void ABaseCharacter::Die(float LifeSpan, bool bEnableRagdoll)
{
	if (!IsAlive())
	{
		DetachFromControllerPendingDestroy();

		/* Disable all collision on capsule */
		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

		SetActorEnableCollision(true);

		if (bEnableRagdoll)
		{
			// Ragdoll
			if (USkeletalMeshComponent* MeshComp = GetMesh())
			{
				MeshComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
				MeshComp->SetCollisionResponseToAllChannels(ECR_Block);

				MeshComp->SetAllBodiesSimulatePhysics(true);
				MeshComp->SetSimulatePhysics(true);
				MeshComp->WakeAllRigidBodies();
			}

			if (UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent()))
			{
				CharacterComp->StopMovementImmediately();
				CharacterComp->DisableMovement();
				CharacterComp->SetComponentTickEnabled(false);
			}
		}

		SetLifeSpan(LifeSpan);
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// No binding by default because this base class for both Player and AICharacter
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ASC.IsValid())
		ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetWalkSpeedAttribute()).RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ABaseCharacterState* PS = GetPlayerState<ABaseCharacterState>();
	if (!PS) return;

	ASC = Cast<UCustomAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	if (!ASC.IsValid()) return;

	ASC->InitAbilityActorInfo(PS, this);

	// TODO: Consider where to this to get replicated
	// Bind Attribute Value Change Delegates before Init Attributes to catch init value and assign these value to ACharacter
	BindAttributeValueChangeDelegates();
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

void ABaseCharacter::BindAttributeValueChangeDelegates()
{
	if (!ASC.IsValid()) return;

	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetWalkSpeedAttribute()).AddUObject(
		this, &ABaseCharacter::OnWalkSpeedAttributeValueChange);
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

void ABaseCharacter::OnWalkSpeedAttributeValueChange(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}
