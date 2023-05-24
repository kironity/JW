// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JWWeaponMagazine.generated.h"

class AJWRangeWeapon;
class UBoxComponent;

UCLASS()
class JW_API AJWWeaponMagazine : public AActor
{
	GENERATED_BODY()

public:
	AJWWeaponMagazine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MagazineDefaults")
	UStaticMeshComponent* MagazineMesh;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetAmmoInClip() { return AmmoInClip; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetMaxAmmoInClip() { return MaxAmmoInClip; }

	UFUNCTION(BlueprintCallable)
	void SetAmmoInClip(int32 InAmmoInClip);

	UFUNCTION(BlueprintCallable)
	void SetMaxAmmoInClip(int32 InMaxAmmoInClip);

	UFUNCTION(BlueprintCallable)
	AJWRangeWeapon* GetOwningWeapon();
private:
	UPROPERTY(EditDefaultsOnly)
	int32 AmmoInClip;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmoInClip;
};
