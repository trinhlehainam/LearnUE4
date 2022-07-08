// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseNPC.h"

#include "Controllers/NPCController.h"

ABaseNPC::ABaseNPC()
{
	AIControllerClass = ANPCController::StaticClass();
}

void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseNPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}