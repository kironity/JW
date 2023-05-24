// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JWHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthValueChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JW_API UJWHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJWHealthComponent();

#pragma region GettersAndSetters
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetMinHealthValue() const { return MinHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetMaxHealthValue() const { return MaxHealth; }
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float InHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMinHealth(float InMinHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMaxHealth(float InMaxHealth);
#pragma endregion 

	UFUNCTION(BlueprintCallable, Category = "Health")
	void DegreaseHealth(float DegreaseValue);

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnHealthValueChanged OnHealthValueChanged;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "HealthSettings")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "HealthSettings")
	float MinHealth;

	UPROPERTY(EditDefaultsOnly, Category = "HealthSettings")
	float MaxHealth;
};
