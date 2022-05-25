// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "CharacterCombatComponent.h"
#include "EnemyController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CombatComponent = CreateDefaultSubobject<UCharacterCombatComponent>(Fname("Combat Component"));
	ArgoSphere = CreateDefaultSubobject<USphereComponent>(FName("Argo Range"));
	AttackSphere = CreateDefaultSubobject<USphereComponent>(FName("Attack Range"));

	ArgoSphere->SetupAttachment(RootComponent);
	AttackSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	FVector Location = GetActorLocation();
	EnemyController = Cast<AEnemyController>(GetController());
	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint1"), Location + PatrolPoint1);
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint2"), Location + PatrolPoint2);
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint3"), Location + PatrolPoint3);
	BlackboardComponent->SetValueAsVector(FName("PatrolPoint4"), Location + PatrolPoint4);

	ArgoSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::ArgoBeginOverlap);
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AttackBeginOverlap);

	ArgoSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::ArgoEndOverlap);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AttackEndOverlap);

	CombatComponent->OnAttack.BindUObject(this, &AEnemy::Attack);
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

void AEnemy::ArgoBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	bIsInAttackRange = true;
	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool(FName("IsInAttackRange"), true);
}

void AEnemy::ArgoEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	bIsInAttackRange = false;
	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool(FName("IsInAttackRange"), false);
}

void AEnemy::AttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsObject(FName("TargetActor"), OtherActor);
}

void AEnemy::AttackEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsObject(FName("TargetActor"), nullptr);
}

void AEnemy::Attack()
{
	if (!CombatComponent) return;

	if (CombatComponent->bIsAttacking) return;

	CombatComponent->bIsAttacking = true;

	auto AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatComponent->GetAnimMontage())
	{
		AnimInstance->Montage_Play(CombatComponent->GetAnimMontage());
	}
}
