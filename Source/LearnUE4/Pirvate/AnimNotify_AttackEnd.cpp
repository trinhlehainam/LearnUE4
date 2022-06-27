// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackEnd.h"

#include "MyCharacter.h"

void UAnimNotify_AttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp) return;
	
	AActor* owner = MeshComp->GetOwner();
	if (!owner) return;

}
