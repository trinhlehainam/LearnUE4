// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_NPCMoveToLocation.h"

#include "Controllers/NPCController.h"
#include "NavigationPath.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Characters/BaseNPC.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_NPCMoveToLocation::UBTTask_NPCMoveToLocation(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer)
{
	NodeName = "NPC Move To Location";

	// accept vector only
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_NPCMoveToLocation, BlackboardKey));
}

FString UBTTask_NPCMoveToLocation::GetStaticDescription() const
{
	FString ClassDesc("MoveTo");
	FString KeyDesc("invalid");
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		KeyDesc = BlackboardKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("%s: %s"), *ClassDesc, *KeyDesc);
}

EBTNodeResult::Type UBTTask_NPCMoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BlackboardKey.SelectedKeyType != UBlackboardKeyType_Vector::StaticClass())
		return EBTNodeResult::Failed;

	ANPCController* NPCController = Cast<ANPCController>(OwnerComp.GetAIOwner());
	ABaseNPC* NPC = Cast<ABaseNPC>(NPCController->GetPawn());
	if (!NPCController || !NPC) return EBTNodeResult::Failed;

	FVector Destination = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	EPathFollowingRequestResult::Type RequestResult = NPCController->MoveToLocation(Destination);

	if (RequestResult == EPathFollowingRequestResult::Failed) return EBTNodeResult::Failed;

	if (RequestResult == EPathFollowingRequestResult::AlreadyAtGoal) return EBTNodeResult::Succeeded;

	FAIRequestID RequestID = NPCController->GetCurrentMoveRequestID();
	WaitForMessage(OwnerComp, UBrainComponent::AIMessage_MoveFinished, RequestID);

	return EBTNodeResult::InProgress;
}

void UBTTask_NPCMoveToLocation::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message,
                                         int32 RequestID, bool bSuccess)
{
	// AIMessage_RepathFailed means task has failed
	bSuccess &= (Message != UBrainComponent::AIMessage_RepathFailed);
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestID, bSuccess);
}
