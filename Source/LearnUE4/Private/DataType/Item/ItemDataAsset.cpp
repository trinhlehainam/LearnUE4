// Fill out your copyright notice in the Description page of Project Settings.


#include "DataType/Item/ItemDataAsset.h"

#include "DataType/CustomAssetManager.h"

UItemDataAsset::UItemDataAsset()
{
}

FPrimaryAssetId UItemDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, ItemName);
}
