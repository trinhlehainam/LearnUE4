// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GEExecCalc_Damage.h"

#include "Abilities/BaseAttributeSet.h"

// TODO: Put this to global file for every source can use this
// When we put our properties in *private* or *protected* of Attribute class, GET_MEMBER_NAME_CHECKED macro in
// DEFINE_ATTRIBUTE_CAPTUREDEF can't access these properties. So we need to write our own macro.
#define DEFINE_ATTRIBUTE_CAPTUREDEF_CUSTOM(S, P, T, B) \
{ \
	P##Property = S::Get##P##Attribute().GetUProperty(); \
	P##Def = FGameplayEffectAttributeCaptureDefinition(P##Property, EGameplayEffectAttributeCaptureSource::T, B); \
}

namespace
{
	struct FAttributeCaptures
	{
		DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
		DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

		FAttributeCaptures()
		{
			DEFINE_ATTRIBUTE_CAPTUREDEF_CUSTOM(UBaseAttributeSet, Health, Target, false);
			DEFINE_ATTRIBUTE_CAPTUREDEF_CUSTOM(UBaseAttributeSet, AttackPower, Source, true);
		}
	};

}

const FAttributeCaptures& AttributeCaptures()
{
	// TODO: Write document
	// - We declare FAttributeCaptures as static variable in function-level because
	// we want this variable is initialized when this function is invoked
	// - If we declare this as global variable, when global variable is initialized, maybe UBaseAttributeSet::StaticClass
	// is not defined yet
	static FAttributeCaptures Singleton;
	return Singleton;
}

UGEExecCalc_Damage::UGEExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(AttributeCaptures().HealthDef);
	RelevantAttributesToCapture.Add(AttributeCaptures().AttackPowerDef);	
}

void UGEExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float AttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		AttributeCaptures().AttackPowerDef, EvaluationParameters, AttackPower);

	float Health = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		AttributeCaptures().HealthDef, EvaluationParameters, Health);

	if (AttackPower > 0.f)
	{
		// Set the Target's damage meta attribute
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
				AttributeCaptures().AttackPowerProperty, EGameplayModOp::Additive, AttackPower));
	}
}
