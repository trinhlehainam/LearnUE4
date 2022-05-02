// Fill out your copyright notice in the Description page of Project Settings.


#include "HazardPoison.h"
#include "MyCharacter.h"

AHazardPoison::AHazardPoison()
{
	HazardAmount = 10.f;
}

void AHazardPoison::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AMyCharacter>(OtherActor);
	if (Character) {
		Character->SetHealth(Character->GetHealth() - HazardAmount);
	}

	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
