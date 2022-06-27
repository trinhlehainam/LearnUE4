// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Enemy.h"
#include "BehaviorTree/BehaviorTree.h"

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!InPawn) return;
	
	AEnemy* Enemy = Cast<AEnemy>(InPawn);
	if (!Enemy) return;

	check(UseBlackboard(Enemy->BehaviorTree->BlackboardAsset, Blackboard));
	check(RunBehaviorTree(Enemy->BehaviorTree));
}
