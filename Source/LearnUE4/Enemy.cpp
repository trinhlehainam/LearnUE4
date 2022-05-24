// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	FVector Location = GetActorLocation();
	AIController = Cast<AEnemyController>(GetController());
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint1"), Location + PatrolPoint1);
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint2"), Location + PatrolPoint2);
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint3"), Location + PatrolPoint3);
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint4"), Location + PatrolPoint4);

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

