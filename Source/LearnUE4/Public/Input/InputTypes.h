// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/BaseGameplayAbility.h"
#include "InputTypes.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FGameplayTagInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	const UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	EAbilityInputID AbilityInputID;
};

/**
 * 
 */
UCLASS()
class LEARNUE4_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindInputActionByGameplayTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InputTag")
	TArray<FGameplayTagInputAction> TagInputs;
};
