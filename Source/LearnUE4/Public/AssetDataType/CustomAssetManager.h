// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CustomAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UCustomAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UCustomAssetManager();
	
	static FPrimaryAssetType GetWeaponItemType();	
	static FPrimaryAssetType GetPoisonItemType();	

	static UCustomAssetManager& Get();
	
	virtual void StartInitialLoading() override;
	
private:
	const FPrimaryAssetType WeaponItemType;
	const FPrimaryAssetType PoisonItemType;
};
