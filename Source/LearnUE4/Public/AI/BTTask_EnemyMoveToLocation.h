// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EnemyMoveToLocation.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UBTTask_EnemyMoveToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_EnemyMoveToLocation(const FObjectInitializer& ObjectInitializer);

	FString GetStaticDescription() const final;

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) final;

	void OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess) final;

};
