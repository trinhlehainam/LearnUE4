// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCombatComponent.h"

// Sets default values for this component's properties
UCharacterCombatComponent::UCharacterCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bIsAttacking = false;
}

void UCharacterCombatComponent::AttackStart()
{
	OnAttackStart.ExecuteIfBound();
	bIsAttacking = true;
}

void UCharacterCombatComponent::AttackEnd()
{
	OnAttackEnd.ExecuteIfBound();
	bIsAttacking = false;
}

// Called when the game starts
void UCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

