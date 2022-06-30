// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyCharacter.h"

#include "Controllers/AIController_Enemy.h"

AEnemyCharacter::AEnemyCharacter()
{
	if (GetMesh())
	{
		GetMesh()->SetCollisionObjectType(ECC_Pawn);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetMesh()->SetGenerateOverlapEvents(false);
	}
	
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AAIController_Enemy* AIController = GetController<AAIController_Enemy>();
	if (AIController)
	{
	
	}
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
