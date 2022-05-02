// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HazardPoison.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API AHazardPoison : public AItem
{
	GENERATED_BODY()
	
public:
	AHazardPoison();

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Properties")
	float HazardAmount;
};
