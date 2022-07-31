// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"

// Sets default values
AInteractableDoor::AInteractableDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(USceneComponent::GetDefaultSceneRootVariableName());
	SetRootComponent(DefaultSceneRoot);
	
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

	DoorStartLocation = DoorMesh->GetComponentLocation();
}

bool AInteractableDoor::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return true;
}

bool AInteractableDoor::HasRequiredGameplayTags_Implementation(const FGameplayTagContainer& InteractorTagContainer)
{
	return InteractorTagContainer.HasAllExact(RequireTags);
}

void AInteractableDoor::UpdateDoorLocation(float Z_Offset)
{
	FVector DoorLocation = DoorStartLocation;
	DoorLocation.Z += Z_Offset;
	DoorMesh->SetWorldLocation(DoorLocation);
}

