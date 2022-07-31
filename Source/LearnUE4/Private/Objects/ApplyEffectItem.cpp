// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/ApplyEffectItem.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"


// Sets default values
AApplyEffectItem::AApplyEffectItem()
{
}

// Called when the game starts or when spawned
void AApplyEffectItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AApplyEffectItem::PreInteract_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent)
{
	Super::PreInteract_Implementation(InteractingActor, InteractedComponent);

	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(InteractingActor);
	if (!ASI) return;
	
	UAbilitySystemComponent* InteractorASC = ASI->GetAbilitySystemComponent();

	FGameplayEffectContextHandle EffectContextHandle = InteractorASC->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = InteractorASC->MakeOutgoingSpec(ApplyEffectClass, 1.f, EffectContextHandle);
	InteractorASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	Destroy();
}
