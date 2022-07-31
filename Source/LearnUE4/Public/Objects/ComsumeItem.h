// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApplyEffectItem.h"
#include "GameFramework/Actor.h"
#include "ComsumeItem.generated.h"

UCLASS()
class LEARNUE4_API AComsumeItem : public AApplyEffectItem
{
	GENERATED_BODY()

public:
	AComsumeItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* KeyMesh;
};
