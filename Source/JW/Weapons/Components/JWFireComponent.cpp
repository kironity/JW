// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/JWFireComponent.h"

#include "Weapons/JWRangeWeapon.h"
#include "Weapons/Projectiles/JWWeaponProjectile.h"

UJWFireComponent::UJWFireComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	AmmoPerShot = 1;
}

void UJWFireComponent::BeginPlay()
{
	Super::BeginPlay();
	check(GetOwner())
	OwningWeapon = CastChecked<AJWRangeWeapon>(GetOwner());
}

void UJWFireComponent::SimulateFire()
{
	if (!IsValid(OwningWeapon)) return;

	if (!CanFire())
	{
		OwningWeapon->StopFire();
		return;
	}
	if (!CanSimulateFire())
	{
		return;
	}

	bPendingSimulateFire = true;

	DegreaseAmmo();
	SpawnProjectile();

	const float ShotDelay = FMath::Max(0.1f, OwningWeapon->GetShotDelay());
	GetWorld()->GetTimerManager().SetTimer(TH_Shot, this, &ThisClass::OnSimulateFireFinish, ShotDelay, false);
}

bool UJWFireComponent::CanFire() const
{
	return OwningWeapon->CanFire();
}

bool UJWFireComponent::CanSimulateFire() const
{
	return !bPendingSimulateFire;
}

void UJWFireComponent::DegreaseAmmo() const
{
	OwningWeapon->SetCurrentAmmo(OwningWeapon->GetCurrentAmmo() - AmmoPerShot);
}

void UJWFireComponent::SpawnProjectile() const
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Owner = OwningWeapon;
	const FTransform SpawnTransform = OwningWeapon->GetMuzzleTransform();
	AJWWeaponProjectile* Projectile = OwningWeapon->GetWorld()->SpawnActor<AJWWeaponProjectile>(
		OwningWeapon->ProjectileTemplate, SpawnTransform, SpawnParameters);
	if (Projectile)
	{
		Projectile->ProjectileDamage = OwningWeapon->GetWeaponDamage();
	}
}

void UJWFireComponent::OnSimulateFireFinish()
{
	if (!IsValid(OwningWeapon)) return;

	bPendingSimulateFire = false;
	const bool bCanShotNext = CanFire() && CanSimulateFire() && OwningWeapon->GetWeaponType() == EWeaponFireType::EAuto;

	if (bCanShotNext)
	{
		SimulateFire();
	}
	else
	{
		OwningWeapon->StopFire();
	}
}

void UJWFireComponent::StopSimulateFire()
{
}
