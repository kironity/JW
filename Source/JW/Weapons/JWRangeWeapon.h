// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JWRangeWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoUpdate);

class AJWWeaponProjectile;
class AJWWeaponMagazine;
class UJWFireComponent;

UENUM(BlueprintType)
enum class EWeaponFireType : uint8
{
	EAuto,
	ESemiAuto,
	ESingle,
};

UCLASS()
class JW_API AJWRangeWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJWRangeWeapon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponDefaults")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	UJWFireComponent* FireComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDefaults")
	USceneComponent* MuzzleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponDefaults")
	USceneComponent* MagazineLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDefaults")
	TSubclassOf<AJWWeaponProjectile> ProjectileTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDefaults")
	TSubclassOf<AJWWeaponMagazine> MagazineTemplate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAmmoUpdate OnAmmoUpdate;
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	bool CanFire() const;

	float GetShotDelay() const;

	float GetWeaponRPM() const;

	UFUNCTION(BlueprintCallable)
	bool GrabMagazine();

	UFUNCTION(BlueprintCallable)
	bool PlaceMagazine(AJWWeaponMagazine* PlacedMagazine);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ammo")
	int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void SetCurrentAmmo(int32 InCurrentAmmo);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ammo")
	int32 GetMaxAmmo() const;

	FTransform GetMuzzleTransform() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AJWWeaponMagazine* GetMagazine() const;

	UFUNCTION(BlueprintCallable)
	void SetWeaponMagazine(AJWWeaponMagazine* InWeaponMagazine);

	UFUNCTION(BlueprintCallable)
	bool IsHaveMagazine() const;

	UFUNCTION(BlueprintCallable)
	void CreateDefaultMagazine();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetWeaponDamage() const { return Damage; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EWeaponFireType GetWeaponType() const { return WeaponType; }

protected:
	UPROPERTY(EditDefaultsOnly)
	float WeaponRPM;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly)
	EWeaponFireType WeaponType;

	UPROPERTY()
	AJWWeaponMagazine* CurrentMagazine;

private:
	bool bWantsFire;
	bool bSimulateFire;
};
