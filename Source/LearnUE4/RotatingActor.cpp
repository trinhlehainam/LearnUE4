// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

// Sets default values
ARotatingActor::ARotatingActor() :
	bIsRotating(true),
	RotationRate(45.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));

	SetRootComponent(Mesh);
	Collider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetActorOfClass(this, AMyCharacter::StaticClass()));
	if (MyCharacter)
		MyCharacter->ToggleRotateDelegate.AddDynamic(this, &ARotatingActor::ToggleRotation);

}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRotating) {
		FRotator Rotator = GetActorRotation();
		Rotator.Yaw += RotationRate * DeltaTime;
		SetActorRotation(Rotator);
	}
}

void ARotatingActor::ToggleRotation()
{
	bIsRotating = !bIsRotating;
}

void ARotatingActor::OnFire_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("On Fire"));
}

