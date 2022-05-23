// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_EnemyMoveToLocation.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UBTT_EnemyMoveToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_EnemyMoveToLocation(const FObjectInitializer& ObjectInitializer);

	virtual FString GetStaticDescription() const override;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
};
