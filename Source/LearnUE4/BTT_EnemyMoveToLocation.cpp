// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EnemyMoveToLocation.h"

#include "Enemy.h"
#include "EnemyController.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTT_EnemyMoveToLocation::UBTT_EnemyMoveToLocation(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	NodeName = "Enemy Move To Location";

	// accept vector only
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_EnemyMoveToLocation, BlackboardKey));
}

FString UBTT_EnemyMoveToLocation::GetStaticDescription() const
{
	FString ClassDesc("MoveTo");
	FString KeyDesc("invalid");
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		KeyDesc = BlackboardKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("%s: %s"), *ClassDesc, *KeyDesc);
}

EBTNodeResult::Type UBTT_EnemyMoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BlackboardKey.SelectedKeyType != UBlackboardKeyType_Vector::StaticClass())
		return EBTNodeResult::Failed;

	AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	AEnemy* Enemy = Cast<AEnemy>(EnemyController->GetPawn());
	if (!EnemyController || !Enemy) return EBTNodeResult::Failed;

	FVector Location = Enemy->GetActorLocation();
	FVector Destination = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, Location, Destination);
	if (!NavigationPath) return EBTNodeResult::Failed;

	for (const auto& PathPoint : NavigationPath->PathPoints)
	{
		
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
	return EBTNodeResult::Succeeded;
}
