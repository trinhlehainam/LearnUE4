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

	UFUNCTION()
	void ArgoBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void ArgoEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex);
	UFUNCTION()
	void AttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                        const FHitResult& SweepResult);
	UFUNCTION()
	void AttackEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                      int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category=Combat)
	class USphereComponent* ArgoSphere;

	UPROPERTY(EditAnywhere, Category=Combat)
	class USphereComponent* AttackSphere;

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI Stats", meta=(MakeEditWidget="true"))
	FVector PatrolPoint4;

	UPROPERTY(VisibleAnywhere, Category="AI Stats")
	bool bIsInAttackRange;

	class AEnemyController* EnemyController;
};