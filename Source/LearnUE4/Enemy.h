// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class LEARNUE4_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;

public:
	UPROPERTY(EditAnywhere, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint1;
	
	UPROPERTY(EditAnywhere, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint2;
	
	UPROPERTY(EditAnywhere, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint3;
	
	UPROPERTY(EditAnywhere, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint4;

	UPROPERTY(VisibleAnywhere, Category="AI Stats")
	bool bIsInAttackRange;

	class AEnemyController* AIController;
};