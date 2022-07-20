// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UItemDataAsset();

	FPrimaryAssetType ItemType;

	FName ItemName;

	FString ItemDescription;

	int32 MaxCapacity;

	TSubclassOf<UBaseGameplayAbility> AbilityClass;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;	
};
