// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseNPC.h"

#include "Controllers/AIController_Enemy.h"

ABaseNPC::ABaseNPC()
{
	AIControllerClass = AAIController_Enemy::StaticClass();
}

void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseNPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}