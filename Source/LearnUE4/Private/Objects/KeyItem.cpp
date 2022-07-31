// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/KeyItem.h"


AKeyItem::AKeyItem()
{
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Key Mesh"));
}