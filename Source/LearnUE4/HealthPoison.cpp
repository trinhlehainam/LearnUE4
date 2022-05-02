// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPoison.h"
#include "MyCharacter.h"

AHealthPoison::AHealthPoison()
{
	HealthAmount = 10.f;
}

void AHealthPoison::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AMyCharacter>(OtherActor);
	if (Character) {
		Character->SetHealth(Character->GetHealth() + HealthAmount);
	}
		
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
