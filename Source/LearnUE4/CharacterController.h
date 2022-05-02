// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUE4_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	// Reference to User Widget Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	TSubclassOf<class UUserWidget> WBP_HUDCharacterStats;

	// Pointer to widget instance after creating it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	UUserWidget* HUDCharaterStats;
};
