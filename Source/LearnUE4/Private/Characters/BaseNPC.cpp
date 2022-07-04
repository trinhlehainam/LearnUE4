// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseNPC.h"

#include "Components/SphereComponent.h"

ABaseNPC::ABaseNPC()
{
}

void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();

	if (AttackRangeSphere)
	{
		AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseNPC::AttackRangeBeginOverlap);
		AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseNPC::AttackRangeEndOverlap);
	}
}

void ABaseNPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABaseNPC::AttackRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABaseNPC::AttackRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}