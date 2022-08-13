// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/WeaponActor.h"

#include "Characters/PlayerCharacter.h"


// Sets default values
AWeaponActor::AWeaponActor()
{
	bCanInteract = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon Mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);

	SetRootComponent(WeaponMesh);
}

void AWeaponActor::SetEnableWeaponOverlapCollison(bool bEnable)
{
	WeaponMesh->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void AWeaponActor::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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
		WeaponMesh->SetCollisionResponseToAllChannels(ECR_Overlap);

		Player->CollectWeapon(this);
	}
}
