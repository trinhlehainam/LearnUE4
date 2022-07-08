// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_EnemyMoveToLocation.h"

#include "Characters/Enemy.h"
#include "Controllers/NPCController.h"
#include "NavigationPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_EnemyMoveToLocation::UBTTask_EnemyMoveToLocation(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer)
{
	NodeName = "Enemy Move To Location";

	// accept vector only
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_EnemyMoveToLocation, BlackboardKey));
}

FString UBTTask_EnemyMoveToLocation::GetStaticDescription() const
{
	FString ClassDesc("MoveTo");
	FString KeyDesc("invalid");
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		KeyDesc = BlackboardKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("%s: %s"), *ClassDesc, *KeyDesc);
}

EBTNodeResult::Type UBTTask_EnemyMoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BlackboardKey.SelectedKeyType != UBlackboardKeyType_Vector::StaticClass())
		return EBTNodeResult::Failed;

	ANPCController* EnemyController = Cast<ANPCController>(OwnerComp.GetAIOwner());
	AEnemy* Enemy = Cast<AEnemy>(EnemyController->GetPawn());
	if (!EnemyController || !Enemy) return EBTNodeResult::Failed;

	FVector Destination = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	EPathFollowingRequestResult::Type RequestResult = EnemyController->MoveToLocation(Destination);

	if (RequestResult == EPathFollowingRequestResult::Failed) return EBTNodeResult::Failed;

	if (RequestResult == EPathFollowingRequestResult::AlreadyAtGoal) return EBTNodeResult::Succeeded;

	FAIRequestID RequestID = EnemyController->GetCurrentMoveRequestID();
	WaitForMessage(OwnerComp, UBrainComponent::AIMessage_MoveFinished, RequestID);

	return EBTNodeResult::InProgress;
}

void UBTTask_EnemyMoveToLocation::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message,
                                         int32 RequestID, bool bSuccess)
{
	// AIMessage_RepathFailed means task has failed
	bSuccess &= (Message != UBrainComponent::AIMessage_RepathFailed);
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestID, bSuccess);
}
