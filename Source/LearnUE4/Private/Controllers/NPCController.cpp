// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPCController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Characters/BaseNPC.h"

void ANPCController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABaseNPC* NPC = GetPawn<ABaseNPC>();

	if (!NPC) return;
	
	UBehaviorTree* NPCBehavior = NPC->GetBehaviorTree();
	if (!NPCBehavior) return;
	
	RunBehaviorTree(NPCBehavior);
}
