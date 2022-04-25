// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AOverlapActor::AOverlapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiate
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));

	// Set up hierarchy
	SetRootComponent(Cast<USceneComponent>(Mesh));
	OverlapBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AOverlapActor::BeginOverlap);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AOverlapActor::EndOverlap);
}

void AOverlapActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AOverlapActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void AOverlapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

