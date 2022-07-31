// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ComsumeItem.h"


AComsumeItem::AComsumeItem()
{
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Key Mesh"));
}