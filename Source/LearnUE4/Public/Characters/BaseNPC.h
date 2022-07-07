// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "AI/PatrolTypes.h"
#include "BaseNPC.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API ABaseNPC : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseNPC();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="AI")
	TArray<FPatrolInfo> PatrolInfos;
};
