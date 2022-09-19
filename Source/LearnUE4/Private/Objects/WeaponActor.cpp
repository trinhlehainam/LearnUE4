// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/WeaponActor.h"

#include "AbilitySystemComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Curves/CurveVector.h"

namespace
{
	const FName GLOW_BLEND_ALPHA_PARAM{"GlowBlendAlpha"};
	const FName GLOW_POWER_PARAM{"GlowPower"};
	const FName FRESNEL_EXPONENT_PARAM{"FresnelExponent"};
	const FName FRESNEL_REFLECT_FRACTION_PARAM{"FresnelReflectFraction"};
	const FName GLOW_COLOR_PARAM{"GlowColor"};
}

// Sets default values
AWeaponActor::AWeaponActor():
	bCanInteract(true),
	// Dynamic Material Instance
	MaterialIndex(0),
	PulseRate(5.f),
	GlowPowerBase(120.f),
	FresnelExponentBase(3.f),
	FresnelReflectFractionBase(4.f)
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Weapon Mesh"));

	WeaponMesh->SetCollisionProfileName(UCollisionProfile::CustomCollisionProfileName);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionObjectType(ECC_WorldStatic);
	WeaponMesh->SetGenerateOverlapEvents(false);

	SetRootComponent(WeaponMesh);
}

void AWeaponActor::SetEnableWeaponOverlapCollison(bool bEnable)
{
	WeaponMesh->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void AWeaponActor::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(OtherActor);
	if (!IsValid(TargetCharacter) || !TargetCharacter->IsAlive()) return;

	ABaseCharacter* SourceCharacter = Cast<ABaseCharacter>(GetAttachParentActor());
	if (!IsValid(SourceCharacter) || !SourceCharacter->IsAlive()) return;

	if (TargetCharacter == SourceCharacter) return;

	UAbilitySystemComponent* SourceASC = SourceCharacter->GetAbilitySystemComponent();
	FGameplayEventData GameplayEventData;
	GameplayEventData.Target = OtherActor;
	SourceASC->HandleGameplayEvent(DamageEventTag, &GameplayEventData);
}

bool AWeaponActor::IsAvailableForInteraction_Implementation(UPrimitiveComponent* InteractedComponent)
{
	return bCanInteract;
}

void AWeaponActor::BeginInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
                                                   APlayerController* InteractingPlayerController)
{
	SetEnableCustomDepth(true);
	EnableGlowMaterial();
}

void AWeaponActor::CancelInteraction_Implementation()
{
	SetEnableCustomDepth(false);
}

void AWeaponActor::OnNewTargetFound_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent)
{
	if (InteractedComponent == WeaponMesh)
	{
		SetEnableCustomDepth(true);
	}
}

void AWeaponActor::OnTargetLost_Implementation(AActor* InteratingActor, UPrimitiveComponent* InteractedComponent)
{
	SetEnableCustomDepth(false);
}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	EnableGlowMaterial();

	WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeaponActor::OnAttackBeginOverlap);
}

void AWeaponActor::OnConstruction(const FTransform& Transform)
{
	// Load item data table
	if (!ItemDataTable) return;

	FItemTableRow* ItemData = nullptr;
	if (ItemRarity == EItemRarity::Uncommon)
		ItemData = ItemDataTable->FindRow<FItemTableRow>(FName("Uncommon"), TEXT(""));
	else if (ItemRarity == EItemRarity::Common)
		ItemData = ItemDataTable->FindRow<FItemTableRow>(FName("Common"), TEXT(""));
	else if (ItemRarity == EItemRarity::Rare)
		ItemData = ItemDataTable->FindRow<FItemTableRow>(FName("Rare"), TEXT(""));
	else if (ItemRarity == EItemRarity::Legendary)
		ItemData = ItemDataTable->FindRow<FItemTableRow>(FName("Legendary"), TEXT(""));

	if (ItemData)
	{
		GlowColor = ItemData->GlowColor;
		WeaponMesh->SetCustomDepthStencilValue(ItemData->StencilValue);
	}

	if (GlowMaterialInstance)
	{
		GlowDynamicMaterialInstance = UMaterialInstanceDynamic::Create(GlowMaterialInstance, this);
		GlowDynamicMaterialInstance->SetVectorParameterValue(GLOW_COLOR_PARAM, GlowColor);
		WeaponMesh->SetMaterial(MaterialIndex, GlowDynamicMaterialInstance);
		
		EnableGlowMaterial();
	}
}

void AWeaponActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdatePulseEffect();
}

void AWeaponActor::SetEnableCustomDepth(bool bEnable)
{
	WeaponMesh->SetRenderCustomDepth(bEnable);
}

void AWeaponActor::EnableGlowMaterial()
{
	if (GlowDynamicMaterialInstance)
		GlowDynamicMaterialInstance->SetScalarParameterValue(GLOW_BLEND_ALPHA_PARAM, 0.f);

	if (!PulseTimer.IsValid())
		GetWorldTimerManager().SetTimer(PulseTimer, PulseRate, true);
}

void AWeaponActor::DisableGlowMaterial()
{
	if (GlowDynamicMaterialInstance)
		GlowDynamicMaterialInstance->SetScalarParameterValue(GLOW_BLEND_ALPHA_PARAM, 1.f);

	GetWorldTimerManager().ClearTimer(PulseTimer);
}

void AWeaponActor::UpdatePulseEffect()
{
	if (PulseTimer.IsValid() && PulseCurve && GlowDynamicMaterialInstance)
	{
		const float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(PulseTimer);
		const FVector CurveValue{PulseCurve->GetVectorValue(ElapsedTime)};

		GlowDynamicMaterialInstance->SetScalarParameterValue(GLOW_POWER_PARAM, GlowPowerBase * CurveValue.X);
		GlowDynamicMaterialInstance->SetScalarParameterValue(FRESNEL_EXPONENT_PARAM,
		                                                     FresnelExponentBase * CurveValue.Y);
		GlowDynamicMaterialInstance->SetScalarParameterValue(FRESNEL_REFLECT_FRACTION_PARAM,
		                                                     FresnelReflectFractionBase * CurveValue.Z);
	}
}

void AWeaponActor::EndInteraction_Implementation(AActor* InteractingActor, UPrimitiveComponent* InteractedComponent,
                                                 APlayerController* InteractingPlayerController)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(InteractingActor))
	{
		bCanInteract = false;

		ApplyEffectsToInteractor(InteractingActor);

		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		WeaponMesh->SetCollisionObjectType(ECC_WorldDynamic);
		WeaponMesh->SetGenerateOverlapEvents(true);

		Player->CollectWeapon(this);
	}

	SetEnableCustomDepth(false);
	DisableGlowMaterial();
}
