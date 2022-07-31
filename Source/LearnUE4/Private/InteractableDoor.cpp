// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

// Sets default values
AInteractableDoor::AInteractableDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Default Root"));
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Mesh"));
	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Switch Mesh"));

	DoorMesh->SetupAttachment(GetRootComponent());
	SwitchMesh->SetupAttachment(GetRootComponent());
	
	DoorMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

// Called when the game starts or when spawned
void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();
}

bool AInteractableDoor::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return true;
}

bool AInteractableDoor::HasRequiredGameplayTags_Implementation(const FGameplayTagContainer& InteractorTagContainer)
{
	return RequireTags.HasAllExact(InteractorTagContainer);
}

void AInteractableDoor::UpdateDoorLocation(float Delta)
{
	FVector DoorLocation = DoorMesh->GetComponentLocation();
	DoorLocation.Z += Delta;
	DoorMesh->SetWorldLocation(DoorLocation);
}

