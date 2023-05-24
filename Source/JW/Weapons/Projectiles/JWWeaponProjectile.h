// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JWWeaponProjectile.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectile, Log, All);

UCLASS()
class JW_API AJWWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:
	AJWWeaponProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileDefaults")
	UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileDefaults")
	USphereComponent* SphereCollision;

public:
	UFUNCTION()
	void OnProjectileStop(const FHitResult& ImpactResult);
	UFUNCTION()
	void OnSphereCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                   const FHitResult& SweepResult);

	
	float ProjectileDamage;
};