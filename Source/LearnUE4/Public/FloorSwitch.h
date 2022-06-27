// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class LEARNUE4_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* Switch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* Door;

	FVector SwitchInitialLocation;
	FVector DoorInitialLocation;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void Activate();

	UFUNCTION(BlueprintImplementableEvent)
	void Deactivate();

	UFUNCTION(BlueprintCallable)
	void UpdateNewLocation(float DoorLocation, float SwitchLocation);
};
