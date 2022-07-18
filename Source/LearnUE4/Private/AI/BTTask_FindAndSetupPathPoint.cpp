// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindAndSetupPathPoint.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_FindAndSetupPathPoint::UBTTask_FindAndSetupPathPoint(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Enemy Move To Location";

	// accept vector for path point position
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindAndSetupPathPoint, BlackboardKey));

	// accept float for wait time value
	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindAndSetupPathPoint, BlackboardKey));
}

FString UBTTask_FindAndSetupPathPoint::GetStaticDescription() const
{
	FString ClassDesc("FindAndSetupPathPoint");
	FString KeyDesc("invalid");
	
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		KeyDesc = BlackboardKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("%s: %s"), *ClassDesc, *KeyDesc);
}

EBTNodeResult::Type UBTTask_FindAndSetupPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTTask_FindAndSetupPathPoint::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message,
	int32 RequestID, bool bSuccess)
{
	// AIMessage_RepathFailed means task has failed
	bSuccess &= (Message != UBrainComponent::AIMessage_RepathFailed);
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestID, bSuccess);
}
