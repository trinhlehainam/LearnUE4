// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Characters/MyCharacter.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Collider"));
	Switch = CreateDefaultSubobject<UStaticMeshComponent>(FName("Switch Mesh"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Mesh"));

	SetRootComponent(Trigger);
	Switch->SetupAttachment(RootComponent);
	Door->SetupAttachment(RootComponent);

	Trigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnEndOverlap);

	SwitchInitialLocation = Switch->GetComponentLocation();
	DoorInitialLocation = Door->GetComponentLocation();
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character)
		Activate();
}

void AFloorSwitch::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character)
		Deactivate();
}

void AFloorSwitch::UpdateNewLocation(float DoorLocation, float SwitchLocation) 
{
	FVector SwitchNewLocation = SwitchInitialLocation;
	SwitchNewLocation.Z += SwitchLocation;
	Switch->SetWorldLocation(SwitchNewLocation);

	FVector DoorNewLocation = DoorInitialLocation;
	DoorNewLocation.Z += DoorLocation;
	Door->SetWorldLocation(DoorNewLocation);
}

