// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InteractableDoor.h"

// Sets default values
AInteractableDoor::AInteractableDoor()
{
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

void AInteractableDoor::UpdateDoorLocation(float Z_Offset)
{
	FVector DoorLocation = DoorStartLocation;
	DoorLocation.Z += Z_Offset;
	DoorMesh->SetWorldLocation(DoorLocation);
}