// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetDataType/CustomAssetManager.h"

DEFINE_LOG_CATEGORY(LogAssetManager);

UCustomAssetManager::UCustomAssetManager():
	WeaponItemType(FName("WeaponType")),
	PoisonItemType(FName("PoisonType"))
{
}

FPrimaryAssetType UCustomAssetManager::GetWeaponItemType()
{
	UCustomAssetManager* Singleton = Cast<UCustomAssetManager>(GEngine->AssetManager);
	if (!Singleton) return FPrimaryAssetType();
	return Singleton->WeaponItemType;
}

FPrimaryAssetType UCustomAssetManager::GetPoisonItemType()
{
	UCustomAssetManager* Singleton = Cast<UCustomAssetManager>(GEngine->AssetManager);
	if (!Singleton) return FPrimaryAssetType();
	return Singleton->PoisonItemType;
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
}
