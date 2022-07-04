// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
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
	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;
	
	UFUNCTION()
	void AttackRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							const FHitResult& SweepResult);
	
	UFUNCTION()
	void AttackRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category=Combat)
	class USphereComponent* AttackRangeSphere;
};
