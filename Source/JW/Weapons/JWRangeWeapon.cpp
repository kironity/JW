// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/JWRangeWeapon.h"

#include "Components/JWFireComponent.h"
#include "Magazine/JWWeaponMagazine.h"
#include "Projectiles/JWWeaponProjectile.h"
#include "JW.h"

AJWRangeWeapon::AJWRangeWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(WeaponMesh);

	MagazineLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MagazineLocation"));
	MagazineLocation->SetupAttachment(WeaponMesh);

	FireComponent = CreateDefaultSubobject<UJWFireComponent>(TEXT("FireComponent"));
	
	WeaponRPM = 60.f;
	Damage = 15.f;
	WeaponType = EWeaponFireType::EAuto;
	
	ProjectileTemplate = AJWWeaponProjectile::StaticClass();
	MagazineTemplate = AJWWeaponMagazine::StaticClass();
}

void AJWRangeWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(FireComponent);
	CreateDefaultMagazine();
}

void AJWRangeWeapon::CreateDefaultMagazine()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Owner = this;
	CurrentMagazine = GetWorld()->SpawnActor<AJWWeaponMagazine>(MagazineTemplate,
																MagazineLocation->GetComponentLocation(),
																MagazineLocation->GetComponentRotation(),
																SpawnParameters);
	if (CurrentMagazine)
	{
		const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, //
																					EAttachmentRule::SnapToTarget, //
																					EAttachmentRule::KeepWorld, //
																					true);
		CurrentMagazine->AttachToComponent(MagazineLocation, AttachmentRules);
		UE_LOG(LogJW, Log, TEXT("CreateDefaultMagazine: %s"), *CurrentMagazine->GetName());
	}
}

void AJWRangeWeapon::StartFire()
{
	bWantsFire = true;
	FireComponent->SimulateFire();
}

void AJWRangeWeapon::StopFire()
{
	bWantsFire = false;
	FireComponent->StopSimulateFire();
}

bool AJWRangeWeapon::CanFire() const
{
	return GetCurrentAmmo() > 0 && bWantsFire && IsHaveMagazine();
}

bool AJWRangeWeapon::IsHaveMagazine() const
{
	return IsValid(CurrentMagazine);
}

float AJWRangeWeapon::GetShotDelay() const
{
	const float ShotDelay = GetWeaponRPM() > 0 ? (1.f / GetWeaponRPM()) * 60 : 1.f;
	return ShotDelay;
}

float AJWRangeWeapon::GetWeaponRPM() const
{
	return WeaponRPM;
}

bool AJWRangeWeapon::GrabMagazine()
{
	if (!IsHaveMagazine()) return false;

	StopFire();
	CurrentMagazine = nullptr;
	OnAmmoUpdate.Broadcast();
	return true;
}

bool AJWRangeWeapon::PlaceMagazine(AJWWeaponMagazine* PlacedMagazine)
{
	if (!IsValid(PlacedMagazine)) return false;

	PlacedMagazine->SetActorEnableCollision(false);

	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, //
																				EAttachmentRule::SnapToTarget, //
																				EAttachmentRule::KeepWorld, //
																				true);
	PlacedMagazine->AttachToComponent(MagazineLocation, AttachmentRules);
	PlacedMagazine->SetOwner(this);
	CurrentMagazine = PlacedMagazine;
	OnAmmoUpdate.Broadcast();
	UE_LOG(LogJW, Log, TEXT("Place magazine complete: %s"), *CurrentMagazine->GetName());
	return true;
}

int32 AJWRangeWeapon::GetCurrentAmmo() const
{
	if (IsHaveMagazine())
	{
		return CurrentMagazine->GetAmmoInClip();
	}
	return 0;
}

void AJWRangeWeapon::SetCurrentAmmo(int32 InCurrentAmmo)
{
	if (IsHaveMagazine())
	{
		CurrentMagazine->SetAmmoInClip(InCurrentAmmo);
		OnAmmoUpdate.Broadcast();
		UE_LOG(LogJW, Log, TEXT("SetCurrentAmmo, %s, %d"), *CurrentMagazine->GetName(), CurrentMagazine->GetAmmoInClip());
	}
}

int32 AJWRangeWeapon::GetMaxAmmo() const
{
	if (IsHaveMagazine())
	{
		return CurrentMagazine->GetMaxAmmoInClip();
	}
	return 0;
}

FTransform AJWRangeWeapon::GetMuzzleTransform() const
{
	return MuzzleLocation->GetComponentTransform();
}

AJWWeaponMagazine* AJWRangeWeapon::GetMagazine() const
{
	return CurrentMagazine;
}

void AJWRangeWeapon::SetWeaponMagazine(AJWWeaponMagazine* InWeaponMagazine)
{
	CurrentMagazine = InWeaponMagazine;
}