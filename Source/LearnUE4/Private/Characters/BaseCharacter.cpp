// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/AttributeSet_BaseAttributes.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Characters/BaseCharacterState.h"
#include "Kismet/GameplayStatics.h"

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
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return ASC.Get();
}

float ABaseCharacter::GetHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetHealthAttribute());
}

float ABaseCharacter::GetMaxHealth() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxHealthAttribute());
}

float ABaseCharacter::GetMana() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetManaAttribute());
}

float ABaseCharacter::GetMaxMana() const
{
	if (!ASC.IsValid())
		return 0.f;
	return ASC.Get()->GetNumericAttribute(UAttributeSet_BaseAttributes::GetMaxManaAttribute());
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// No binding by default because this base class for both Player and AICharacter
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	ABaseCharacterState* PS = GetPlayerState<ABaseCharacterState>();
	if (!PS) return;
	ASC = PS->GetAbilitySystemComponent();

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
	ASC = PS->GetAbilitySystemComponent();

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
			ASC->GiveAbility(FGameplayAbilitySpec(DefaultAbility, 1.0f,
			                                      static_cast<int32>(DefaultAbility.GetDefaultObject()->AbilityInputID),
			                                      this));
		}
	}
}

void ABaseCharacter::SetHealth(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UAttributeSet_BaseAttributes::GetHealthAttribute(), Value);
}

void ABaseCharacter::SetMaxHealth(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UAttributeSet_BaseAttributes::GetMaxHealthAttribute(), Value);
}

void ABaseCharacter::SetMana(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UAttributeSet_BaseAttributes::GetManaAttribute(), Value);
}

void ABaseCharacter::SetMaxMana(float Value)
{
	if (ASC.IsValid())
		ASC->SetNumericAttributeBase(UAttributeSet_BaseAttributes::GetMaxManaAttribute(), Value);
}