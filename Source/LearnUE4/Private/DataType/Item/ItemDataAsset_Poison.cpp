// Fill out your copyright notice in the Description page of Project Settings.


#include "DataType/Item/ItemDataAsset_Poison.h"

#include "DataType/CustomAssetManager.h"

UItemDataAsset_Poison::UItemDataAsset_Poison()
{
	ItemType = UCustomAssetManager::PoisonItemType;
}
