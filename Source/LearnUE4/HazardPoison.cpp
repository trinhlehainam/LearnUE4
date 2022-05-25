// Fill out your copyright notice in the Description page of Project Settings.


#include "HazardPoison.h"
#include "CharacterCombatComponent.h"
#include "GameFramework/Character.h"

AHazardPoison::AHazardPoison()
{
	HazardAmount = 10.f;
}

void AHazardPoison::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;
	
	auto CombatComponent = Cast<UCharacterCombatComponent>(Character->GetComponentByClass(UCharacterCombatComponent::StaticClass()));
	if (!CombatComponent) return;
	
	CombatComponent->SetHealth(CombatComponent->GetHealth() - HazardAmount);

	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
