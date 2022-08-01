// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackStart.h"

void UAnimNotify_AttackStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp) return;

	AActor* MeshOwner = MeshComp->GetOwner();
	if (!MeshOwner) return;
}
