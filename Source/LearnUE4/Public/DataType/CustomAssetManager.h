// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CustomAssetManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustomAssetManager, Log, All);

/**
 * 
 */
UCLASS()
class LEARNUE4_API UCustomAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UCustomAssetManager();
	
	static const FPrimaryAssetType WeaponItemType;
	static const FPrimaryAssetType PoisonItemType;

	static UCustomAssetManager& Get();

	// Init all custom managers here
	virtual void StartInitialLoading() override;
};
