// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "AI/PatrolTypes.h"
#include "BaseNPC.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class LEARNUE4_API ABaseNPC : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseNPC();

	UFUNCTION(BlueprintCallable, Category="AI")
	UBehaviorTree* GetBehaviorTree() const;
	
	UFUNCTION(BlueprintCallable, Category="AI")
	const TArray<FPatrolInfo>& GetPatrolInfos() const;

	UFUNCTION(BlueprintCallable, Category="AI")
	int32 GetCurrentPatrolInfoIndex() const;
	
	UFUNCTION(BlueprintCallable, Category="AI")
	void SetCurrentPatrolInfoIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category="AI")
	int32 GetPatrolDirection() const;

	UFUNCTION(BlueprintCallable, Category="AI")
	void SetPatrolDirection(int32 Value);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="AI")
	TArray<FPatrolInfo> PatrolInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="AI")
	EPatrolMovementType PatrolType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="AI")
	int32 CurrentPatrolInfoIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="AI")
	int32 PatrolDirection;
};