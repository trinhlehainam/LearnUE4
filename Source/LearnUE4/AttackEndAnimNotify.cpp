// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackEndAnimNotify.h"
#include "MyCharacter.h"

void UAttackEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr) {
		auto owner = Cast<AMyCharacter>(MeshComp->GetOwner());
		if (owner)
			owner->bIsAttacking = false;
	}	
}
