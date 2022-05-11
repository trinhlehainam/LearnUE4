// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CharacterSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API UCharacterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UCharacterSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SlotName;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int32 UserIndex;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector WorldLocation;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FRotator WorldRotation;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	float Health;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
	float MaxHealth;
};
