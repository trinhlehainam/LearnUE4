// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "CharacterCombatComponent.h"
#include "EnemyController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CombatComponent = CreateDefaultSubobject<UCharacterCombatComponent>(FName("Combat Component"));
	ArgoSphere = CreateDefaultSubobject<USphereComponent>(FName("Argo Range"));
	AttackSphere = CreateDefaultSubobject<USphereComponent>(FName("Attack Range"));
	WeaponCollider = CreateDefaultSubobject<USphereComponent>(FName("Weapon Collider"));

	ArgoSphere->SetupAttachment(RootComponent);
	AttackSphere->SetupAttachment(RootComponent);
	WeaponCollider->SetupAttachment(GetMesh(), FName("weapon_lSocket"));

	ArgoSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ArgoSphere->SetCollisionObjectType(ECC_WorldDynamic);
	ArgoSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	ArgoSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	AttackSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackSphere->SetCollisionObjectType(ECC_WorldDynamic);
	AttackSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollider->SetCollisionObjectType(ECC_WorldDynamic);
	WeaponCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	AttackTimeMin = 0.1f;
	AttackTimeMax = 0.2f;
	CombatComponent->SetHealth(100.f);
	CombatComponent->SetMaxHealth(100.f);
	CombatComponent->SetDamage(10.f);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AEnemyController>(GetController());
	if (EnemyController)
	{
		FVector Location = GetActorLocation();
		UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
		BlackboardComponent->SetValueAsVector(FName("PatrolPoint1"), Location + PatrolPoint1);
		BlackboardComponent->SetValueAsVector(FName("PatrolPoint2"), Location + PatrolPoint2);
		BlackboardComponent->SetValueAsVector(FName("PatrolPoint3"), Location + PatrolPoint3);
		BlackboardComponent->SetValueAsVector(FName("PatrolPoint4"), Location + PatrolPoint4);
	}

	ArgoSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::ArgoBeginOverlap);
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AttackBeginOverlap);
	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::WeaponBeginOverlap);

	ArgoSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::ArgoEndOverlap);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AttackEndOverlap);
	WeaponCollider->OnComponentEndOverlap.AddDynamic(this, &AEnemy::WeaponEndOverlap);

	CombatComponent->OnAttackStart.BindUObject(this, &AEnemy::OnAttackStart);
	CombatComponent->OnAttackEnd.BindUObject(this, &AEnemy::OnAttackEnd);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	QueryAttack();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::AttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	bIsInAttackRange = true;
	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool(FName("IsInAttackRange"), true);
}

void AEnemy::AttackEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	bIsInAttackRange = false;
	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsBool(FName("IsInAttackRange"), false);
}

void AEnemy::WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	if (OtherActor->GetName() == GetName()) return;

	UCharacterCombatComponent* CombatComp = Cast<UCharacterCombatComponent>(
		OtherActor->GetComponentByClass(UCharacterCombatComponent::StaticClass()));
	if (!CombatComp) return;

	CombatComp->TakeDamage(CombatComponent->GetDamage());
	UE_LOG(LogTemp, Warning, TEXT("Hit Player"));
}

void AEnemy::WeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemy::ArgoBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	UE_LOG(LogTemp, Warning, TEXT("OtherActor : %s"), *OtherActor->GetName());

	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsObject(FName("TargetActor"), OtherActor);
}

void AEnemy::ArgoEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	if (!Cast<AMyCharacter>(OtherActor)) return;

	UBlackboardComponent* BlackboardComponent = EnemyController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsObject(FName("TargetActor"), nullptr);
}

void AEnemy::OnAttackStart()
{
	if (!CombatComponent) return;

	if (CombatComponent->IsAttacking()) return;

	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	auto AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatComponent->GetAnimMontage())
	{
		AnimInstance->Montage_Play(CombatComponent->GetAnimMontage());
		AnimInstance->Montage_JumpToSection(FName("Attack"), CombatComponent->GetAnimMontage());
	}
}

void AEnemy::OnAttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Attack End"));
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemy::QueryAttack()
{
	if (!bIsInAttackRange) return;

	if (!CombatComponent) return;

	if (CombatComponent->IsAttacking()) return;

	if (GetWorldTimerManager().TimerExists(AttackTimerHandle)) return;

	float Timer = FMath::RandRange(AttackTimeMin, AttackTimeMax);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, CombatComponent, &UCharacterCombatComponent::AttackStart, Timer);
}
