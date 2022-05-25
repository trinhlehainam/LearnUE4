// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCombatComponent.generated.h"

DECLARE_DELEGATE(FAttackDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LEARNUE4_API UCharacterCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterCombatComponent();

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE void SetHealth(float amount) { Health = FMath::Clamp(amount, 0.f, MaxHealth); }
	FORCEINLINE void SetMaxHealth(float amount) { MaxHealth = amount; }
	
	FORCEINLINE void TakeDamage(float amount) { Health = FMath::Max(Health - amount, 0.f); }
	FORCEINLINE float GetDamage() const { return Damage; }
	FORCEINLINE void SetDamage(float amount) { Damage = amount; }

	FORCEINLINE UAnimMontage* GetAnimMontage() const { return AnimMontage;}

	void Attack();

	bool bIsAttacking;

	FAttackDelegate OnAttack;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats", meta = (AllowPrivateAccess = "true"))
	float Damage;
};
