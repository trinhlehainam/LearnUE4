// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "CharacterController.h"
#include "CharacterSaveGame.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

#include "RotatingActor.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

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

	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera->bUsePawnControlRotation = false;

	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bIsAttacking = false;

	Health = 80.f;
	MaxHealth = 100.f;
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

	TArray<AActor*> actors;
	FVector location = GetActorLocation();
	UGameplayStatics::GetAllActorsOfClass(this, ARotatingActor::StaticClass(), actors);
	for (auto actor : actors)
	{
		UNavigationPath* path = UNavigationSystemV1::FindPathToActorSynchronously(this, location, actor);
		for (auto pathPoint : path->PathPoints)
			DrawDebugSphere(GetWorld(), pathPoint, 30.f, 16, FColor::Red);
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
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAction("ToggleRotation", IE_Pressed, this, &AMyCharacter::ToggleRotationWithDelegate);
	PlayerInputComponent->BindAction("TogglePauseMenu", IE_Pressed, this, &AMyCharacter::TogglePauseMenu);
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

void AMyCharacter::Attack()
{
	if (bIsAttacking) return;

	bIsAttacking = true;

	auto AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AnimMontage)
		AnimInstance->Montage_Play(AnimMontage);
}

void AMyCharacter::ToggleRotationWithDelegate()
{
	ToggleRotateDelegate.Broadcast();
}

void AMyCharacter::SaveData()
{
	if (UCharacterSaveGame* SaveGameInstance =
		Cast<UCharacterSaveGame>(UGameplayStatics::CreateSaveGameObject(UCharacterSaveGame::StaticClass())))
	{
		SlotName = SaveGameInstance->SlotName;
		SaveGameInstance->WorldLocation = GetActorLocation();
		SaveGameInstance->WorldRotation = GetActorRotation();
		SaveGameInstance->Health = Health;
		SaveGameInstance->MaxHealth = MaxHealth;

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
		Health = LoadGameInstance->Health;
		MaxHealth = LoadGameInstance->MaxHealth;

		UE_LOG(LogTemp, Warning, TEXT("Load : [Health : %f MaxHealth : %f]"), LoadGameInstance->Health,
		       LoadGameInstance->MaxHealth);
	}
}

void AMyCharacter::TogglePauseMenu()
{
	if (Controller)
	{
		ACharacterController* CharaController = Cast<ACharacterController>(Controller);
		CharaController->TogglePauseMenu();
	}
}
