// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApplyEffectItem.h"
#include "GameFramework/Actor.h"
#include "KeyItem.generated.h"

UCLASS()
class LEARNUE4_API AKeyItem : public AApplyEffectItem
{
	GENERATED_BODY()

public:
	AKeyItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* KeyMesh;
};
