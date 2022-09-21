// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemRarity: uint8
{
	Uncommon,
	Common,
	Rare,
	Epic,
	Legendary
};

UENUM(BlueprintType)
enum class EItemType: uint8
{
	Weapon	
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct LEARNUE4_API FItemTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor GlowColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StencilValue;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BackgroundIcon;
};
