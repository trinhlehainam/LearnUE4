// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackStart.h"

#include "Characters/MyCharacter.h"

void UAnimNotify_AttackStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp) return;

	AActor* MeshOwner = MeshComp->GetOwner();
	if (!MeshOwner) return;

	AMyCharacter* Player = Cast<AMyCharacter>(MeshOwner);
	if (Player)
	{
		Player->BeginAttack();
	}
}
