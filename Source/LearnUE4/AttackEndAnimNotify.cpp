// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackEndAnimNotify.h"

#include "CharacterCombatComponent.h"
#include "MyCharacter.h"

void UAttackEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;
	
	AActor* owner = MeshComp->GetOwner();
	if (!owner) return;

	UCharacterCombatComponent* CombatComponent = Cast<UCharacterCombatComponent>(owner->GetComponentByClass(UCharacterCombatComponent::StaticClass()));
	if (!CombatComponent) return;
	CombatComponent->bIsAttacking = false;
}
