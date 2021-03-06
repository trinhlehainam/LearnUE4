// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "AbilitySystemComponent.h"
#include "Characters/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	SetRootComponent(Collider);
	Mesh->SetupAttachment(RootComponent);

	bIsRotate = false;
	RotationRate = 30.0f;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
}

bool AItem::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractingComponent)
{
	return true;
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DrawDebugSphere(GetWorld(), GetActorLocation(), Collider->GetScaledSphereRadius(), 64, FColor::Red);

	if (bIsRotate) {
		FRotator Rotator = GetActorRotation();
		Rotator.Yaw += RotationRate;
		SetActorRotation(Rotator);
	}
}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!PoisonEffect) return;
	
	auto Character = Cast<ABaseCharacter>(OtherActor);
	if (!Character) return;
	UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();
	if (!ASC) return;

	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(PoisonEffect, 1, Context);
	if (Spec.IsValid())
	{
		ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
	
	Destroy();
}