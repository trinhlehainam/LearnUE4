// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCController.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API ANPCController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
