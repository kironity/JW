// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Magazine/JWWeaponMagazine.h"

#include "Weapons/JWRangeWeapon.h"

AJWWeaponMagazine::AJWWeaponMagazine()
{
	PrimaryActorTick.bCanEverTick = false;
	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagazineMesh"));
	SetRootComponent(MagazineMesh);
	MagazineMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	MagazineMesh->SetGenerateOverlapEvents(true);
	
	MaxAmmoInClip = 20;
	AmmoInClip = MaxAmmoInClip; 
}

void AJWWeaponMagazine::BeginPlay()
{
	Super::BeginPlay();
}

void AJWWeaponMagazine::SetAmmoInClip(int32 InAmmoInClip)
{
	AmmoInClip = FMath::Max(0, InAmmoInClip);
}

void AJWWeaponMagazine::SetMaxAmmoInClip(int32 InMaxAmmoInClip)
{
	MaxAmmoInClip = FMath::Max(0,InMaxAmmoInClip);
}

AJWRangeWeapon* AJWWeaponMagazine::GetOwningWeapon()
{
	return Cast<AJWRangeWeapon>(GetOwner());
}
