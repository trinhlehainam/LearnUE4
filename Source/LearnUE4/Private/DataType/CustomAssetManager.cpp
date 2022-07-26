// Fill out your copyright notice in the Description page of Project Settings.


#include "DataType/CustomAssetManager.h"

#include "CustomAbilitySystemGlobals.h"
#include "Abilities/CustomGameplayTags.h"

DEFINE_LOG_CATEGORY(LogAssetManager);

const FPrimaryAssetType UCustomAssetManager::WeaponItemType = FName("WeaponType");
const FPrimaryAssetType UCustomAssetManager::PoisonItemType = FName("PoisonType");

UCustomAssetManager::UCustomAssetManager()
{
}

UCustomAssetManager& UCustomAssetManager::Get()
{
	UCustomAssetManager* Singleton = Cast<UCustomAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogAssetManager, Fatal, TEXT("Cannot use UCustomAssetManager if no AssetManagerClassName is defined!"));
		return *NewObject<UCustomAssetManager>(); // never calls this
	}
}

void UCustomAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UCustomAbilitySystemGlobals::Get().InitGlobalData();
	FCustomGameplayTags::Get();
}
