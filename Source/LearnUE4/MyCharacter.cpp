// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "AbilitySystemComponent.h"
#include "CharacterController.h"
#include "CharacterSaveGame.h"
#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"
#include "MyAttributeSet.h"
#include "MyGameplayAbility.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "NavigationSystem.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't let Controller rotating Character
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Let Character Movement Component rotate Character toward movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(FName("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	bIsAbilitiesBoundToInput = false;

	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera->bUsePawnControlRotation = false;

	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	if (GetMesh())
	{
		GetMesh()->SetCollisionObjectType(ECC_Pawn);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetMesh()->SetGenerateOverlapEvents(false);
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Cyan, FString::Printf(TEXT("DeltaTime : %f"), DeltaTime));

	if (CameraBoom)
	{
		TArray<FHitResult> HitResults;
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);
		GetWorld()->SweepMultiByChannel(HitResults, GetActorLocation(), CameraBoom->GetUnfixedCameraPosition(),
		                                FQuat::Identity, ECC_Camera,
		                                FCollisionShape::MakeSphere(CameraBoom->ProbeSize), CollisionQueryParams);
		DrawSphereSweeps(GetWorld(), GetActorLocation(), CameraBoom->GetUnfixedCameraPosition(), CameraBoom->ProbeSize, HitResults, -1.f);
		for (const auto& HitResult : HitResults)
			if (HitResult.bBlockingHit)
				DrawDebugSphere(GetWorld(), HitResult.Location, CameraBoom->ProbeSize, 16, FColor::Yellow);
		if (CameraBoom->IsCollisionFixApplied())
			UE_LOG(LogTemp, Warning, TEXT("Camera Boom Collision"));
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("StopJump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("TogglePauseMenu", IE_Pressed, this, &AMyCharacter::TogglePauseMenu);

	BindAbilitiesActivationToInputComponent();
}

void AMyCharacter::MoveFoward(float scale)
{
	if ((Controller != NULL) && (scale != 0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, scale);
	}
}

void AMyCharacter::MoveRight(float scale)
{
	if ((Controller != NULL) && (scale != 0.f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, scale);
	}
}

void AMyCharacter::OnAttackStart()
{
	
}

void AMyCharacter::SaveData()
{
	if (UCharacterSaveGame* SaveGameInstance =
		Cast<UCharacterSaveGame>(UGameplayStatics::CreateSaveGameObject(UCharacterSaveGame::StaticClass())))
	{
		SlotName = SaveGameInstance->SlotName;
		SaveGameInstance->WorldLocation = GetActorLocation();
		SaveGameInstance->WorldRotation = GetActorRotation();

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SlotName, SaveGameInstance->UserIndex))
		{
			UE_LOG(LogTemp, Warning, TEXT("Save success"));
		}
	}
}

void AMyCharacter::LoadData()
{
	UCharacterSaveGame* LoadGameInstance = Cast<UCharacterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (LoadGameInstance)
	{
		SetActorLocation(LoadGameInstance->WorldLocation);
		SetActorRotation(LoadGameInstance->WorldRotation);

		UE_LOG(LogTemp, Warning, TEXT("Load : [Health : %f MaxHealth : %f]"), LoadGameInstance->Health,
		       LoadGameInstance->MaxHealth);
	}
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ASC)
	{
		ASC->AddSet<UMyAttributeSet>();
	}
}

void AMyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ASC->InitAbilityActorInfo(this, this);
	InitAttributes();
	GiveDefaultAbilities();
}

void AMyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ASC->InitAbilityActorInfo(this, this);
	InitAttributes();
	BindAbilitiesActivationToInputComponent();
}

float AMyCharacter::GetHealth() const
{
	if (ASC)
		return ASC->GetNumericAttribute(UMyAttributeSet::GetHealthAttribute());
	return 0.f;
}

float AMyCharacter::GetMaxHealth() const
{
	if (ASC)
		return ASC->GetNumericAttribute(UMyAttributeSet::GetMaxHealthAttribute());
	return 0.f;
}

float AMyCharacter::GetMana() const
{
	if (ASC)
		return ASC->GetNumericAttribute(UMyAttributeSet::GetManaAttribute());
	return 0.f;
}

float AMyCharacter::GetMaxMana() const
{
	if (ASC)
		return ASC->GetNumericAttribute(UMyAttributeSet::GetMaxManaAttribute());
	return 0.f;
}

void AMyCharacter::InitAttributes()
{
	if (ASC && DefaultGameplayEffect)
	{
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		Context.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultGameplayEffect, 1, Context);
		if (SpecHandle.IsValid())
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void AMyCharacter::GiveDefaultAbilities()
{
	if (HasAuthority() && ASC)
	{
		for (TSubclassOf<UMyGameplayAbility>& DefaultAbility : DefaultAbilities)
		{
			ASC->GiveAbility(FGameplayAbilitySpec(DefaultAbility, 1.0f,
				static_cast<int32>(DefaultAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

void AMyCharacter::BindAbilitiesActivationToInputComponent()
{
	if (InputComponent && ASC && !bIsAbilitiesBoundToInput)
	{
		FGameplayAbilityInputBinds BindInfo("Confirm", "Cancel", "EAbilityInputID",
			static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel));
		ASC->BindAbilityActivationToInputComponent(InputComponent, BindInfo);
		bIsAbilitiesBoundToInput = true;
	}
}

UAbilitySystemComponent* AMyCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMyCharacter::TogglePauseMenu()
{
	if (Controller)
	{
		ACharacterController* CharaController = Cast<ACharacterController>(Controller);
		CharaController->TogglePauseMenu();
	}
}

void AMyCharacter::HealthAttributeUpdated(const FOnAttributeChangeData& Data)
{
	OnHealthAttributeChange.Broadcast(Data.NewValue);
}

void AMyCharacter::MaxHealthAttributeUpdated(const FOnAttributeChangeData& Data)
{
	OnMaxHealthAttributeChange.Broadcast(Data.NewValue);
}
