// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthPoison.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API AHealthPoison : public AItem
{
	GENERATED_BODY()
	
public:
	AHealthPoison();

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Properties")
	float HealthAmount;
};
