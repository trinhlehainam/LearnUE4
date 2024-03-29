// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interactable.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class LEARNUE4_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetEnableCustomDepth(bool bEnable);

public:
	virtual bool IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractingComponent) override;
	virtual void BeginInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
	                                             APlayerController* InteractingPlayerController) override;
	virtual void EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
	                                           APlayerController* InteractingPlayerController) override;
	virtual void CancelInteraction_Implementation() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Collision)
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Collision")
	class USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Effect")
	TSubclassOf<class UGameplayEffect> PoisonEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	bool bIsRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	float RotationRate;
};
