// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPoison.h"
#include "GameFramework/Character.h"


AHealthPoison::AHealthPoison()
{
	HealthAmount = 10.f;
}

void AHealthPoison::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Increase Health"));

	auto Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;
	
		
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

DEFINE_LOG_CATEGORY(LogCustom);