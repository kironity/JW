// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/JWRangeWeapon.h"
#include "JWFireComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JW_API UJWFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJWFireComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SimulateFire();
	virtual void StopSimulateFire();

	virtual void OnSimulateFireFinish();

	bool CanFire() const;
	bool CanSimulateFire() const;

	void DegreaseAmmo() const;

	void SpawnProjectile() const;

protected:
	bool bPendingSimulateFire;

	UPROPERTY()
	AJWRangeWeapon* OwningWeapon;

	UPROPERTY(EditDefaultsOnly)
	int32 AmmoPerShot;

	UPROPERTY()
	FTimerHandle TH_Shot;
};
