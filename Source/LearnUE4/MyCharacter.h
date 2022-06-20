// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToggleRotateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChange, float, Data);

struct FOnAttributeChangeData;

UCLASS()
class LEARNUE4_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveFoward(float scale);

	void MoveRight(float scale);

	void OnAttackStart();

	FString SlotName;
	void SaveData();
	void LoadData();

	/*GAMEPLAY ABILITY SYSTEM*/
	virtual void PostInitializeComponents() override;
	// Server-side
	virtual void PossessedBy(AController* NewController) override;
	// Client-side : Client received replicated PlayerState from Server
	virtual void OnRep_PlayerState() override;

	float GetHealth() const;
	float GetMaxHealth() const;
	float GetMana() const;
	float GetMaxMana() const;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void InitAttributes();
	void GiveDefaultAbilities();
	void BindAbilitiesActivationToInputComponent();

	FOnAttributeChange OnHealthAttributeChange;
	FOnAttributeChange OnMaxHealthAttributeChange;
	/**/
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	UAbilitySystemComponent* ASC;

	bool bIsAbilitiesBoundToInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay Ability|Default Ability", meta=(AllowPrivateAccess))
	TSubclassOf<class UGameplayEffect> DefaultGameplayEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay Ability|Default Ability", meta=(AllowPrivateAccess))
	TArray<TSubclassOf<class UMyGameplayAbility>> DefaultAbilities;

	void TogglePauseMenu();

	void HealthAttributeUpdated(const FOnAttributeChangeData& Data);
	void MaxHealthAttributeUpdated(const FOnAttributeChangeData& Data);
};
