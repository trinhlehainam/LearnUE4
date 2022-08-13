// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InteractableActorBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"


// Sets default values
AInteractableActorBase::AInteractableActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AInteractableActorBase::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return true;
}

bool AInteractableActorBase::HasRequiredGameplayTags_Implementation(const FGameplayTagContainer& InteractorTagContainer)
{
	return InteractorTagContainer.HasAllExact(RequireTags);
}

bool AInteractableActorBase::ApplyEffectsToInteractor(AActor* Interactor)
{
	if (!ApplyEffectClass) return false;
	
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Interactor);
	if (!ASI) return false;
	
	UAbilitySystemComponent* InteractorASC = ASI->GetAbilitySystemComponent();

	FGameplayEffectContextHandle EffectContextHandle = InteractorASC->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = InteractorASC->MakeOutgoingSpec(ApplyEffectClass, 1.f, EffectContextHandle);
	InteractorASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	return true;
}
