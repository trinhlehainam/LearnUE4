// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseNPC.h"

#include "Controllers/NPCController.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseNPC::ABaseNPC()
{
	AIControllerClass = ANPCController::StaticClass();
	CurrentPatrolInfoIndex = 0;
	PatrolDirection = 1;

	// Set up Smooth Character Rotation when moving
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->RotationRate.Yaw = 180.f;
		MoveComp->bOrientRotationToMovement = true;

		// Also set up bUseAccelerationForPaths in Blueprint for AI control Character acceleration
	}
}

void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseNPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

const TArray<FPatrolInfo>& ABaseNPC::GetPatrolInfos() const
{
	return PatrolInfos;
}

int32 ABaseNPC::GetCurrentPatrolInfoIndex() const
{
	return CurrentPatrolInfoIndex;
}

void ABaseNPC::SetCurrentPatrolInfoIndex(int32 Index)
{
	CurrentPatrolInfoIndex = Index;
}

int32 ABaseNPC::GetPatrolDirection() const
{
	return PatrolDirection;
}

void ABaseNPC::SetPatrolDirection(int32 Value)
{
	PatrolDirection = Value;
}

UBehaviorTree* ABaseNPC::GetBehaviorTree() const
{
	return BehaviorTree;
}
