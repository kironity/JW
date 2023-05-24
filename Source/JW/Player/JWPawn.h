// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "JWPawn.generated.h"

class UJWHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

UCLASS()
class JW_API AJWPawn : public ACharacter
{
	GENERATED_BODY()

public:
	AJWPawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	UJWHealthComponent* HealthComponent;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Player")
	FOnPlayerDeath OnPlayerDeath;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnReceiveAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                        class AController* InstigatedBy, AActor* DamageCauser);

	bool IsAlive() const;

	UFUNCTION()
	void ApplyActualDamage(float Damage);

	bool CanDie() const;

	void Die();

private:
	bool bIsDying;
};
