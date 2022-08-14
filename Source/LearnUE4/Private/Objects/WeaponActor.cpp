// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/WeaponActor.h"

#include "AbilitySystemComponent.h"
#include "Characters/PlayerCharacter.h"


// Sets default values
AWeaponActor::AWeaponActor()
{
	bCanInteract = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon Mesh"));
	
	WeaponMesh->SetCollisionProfileName(UCollisionProfile::CustomCollisionProfileName);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionObjectType(ECC_WorldStatic);
	WeaponMesh->SetGenerateOverlapEvents(false);

	SetRootComponent(WeaponMesh);
}

void AWeaponActor::SetEnableWeaponOverlapCollison(bool bEnable)
{
	WeaponMesh->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void AWeaponActor::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(OtherActor);
	if (!IsValid(TargetCharacter) || !TargetCharacter->IsAlive()) return;

	ABaseCharacter* SourceCharacter = Cast<ABaseCharacter>(GetAttachParentActor());
	if (!IsValid(SourceCharacter) || !SourceCharacter->IsAlive()) return;

	if (TargetCharacter == SourceCharacter) return;

	UAbilitySystemComponent* SourceASC = SourceCharacter->GetAbilitySystemComponent();
	FGameplayEventData GameplayEventData;
	GameplayEventData.Target = OtherActor;
	SourceASC->HandleGameplayEvent(DamageEventTag, &GameplayEventData);
}

bool AWeaponActor::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return bCanInteract;
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeaponActor::OnAttackBeginOverlap);
}

void AWeaponActor::EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
                                                 APlayerController* InteractingPlayerController)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(InteractingActor))
	{
		bCanInteract = false;

		ApplyEffectsToInteractor(InteractingActor);

		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		WeaponMesh->SetCollisionObjectType(ECC_WorldDynamic);
		WeaponMesh->SetGenerateOverlapEvents(true);

		Player->CollectWeapon(this);
	}
}
