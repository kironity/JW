// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectiles/JWWeaponProjectile.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogProjectile);

AJWWeaponProjectile::AJWWeaponProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComponent->Velocity = FVector(1500.f, 0.f, 0.f);
	ProjectileComponent->OnProjectileStop.AddDynamic(this, &ThisClass::OnProjectileStop);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlap"));
	SetRootComponent(SphereCollision);
	SphereCollision->InitSphereRadius(2.f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereCollisionBeginOverlap);
}

void AJWWeaponProjectile::OnProjectileStop(const FHitResult& ImpactResult)
{
	if (IsValid(ImpactResult.GetActor()))
	{
		UGameplayStatics::ApplyPointDamage(ImpactResult.GetActor(), ProjectileDamage, GetVelocity().GetUnsafeNormal(), ImpactResult,
										   nullptr, this, UDamageType::StaticClass());
		UE_LOG(LogProjectile, Log, TEXT("Apply point damage")); 
	}
	Destroy();
}

void AJWWeaponProjectile::OnSphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (IsValid(OtherComp))
	{
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulse(ProjectileComponent->Velocity * 1.f);
			UE_LOG(LogProjectile, Log, TEXT("Apply implulse")); 
			Destroy();
		}
	}
	if (IsValid(OtherActor) && OtherActor != GetOwner())
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, ProjectileDamage, GetVelocity().GetUnsafeNormal(), SweepResult,
		                                   nullptr, this, UDamageType::StaticClass());
		UE_LOG(LogProjectile, Log, TEXT("Apply point damage")); 
	}
}
