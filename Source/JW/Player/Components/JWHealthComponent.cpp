// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/JWHealthComponent.h"

UJWHealthComponent::UJWHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	MinHealth = 0.f;
	MaxHealth = 100.f;
	SetHealth(MaxHealth);
}

float UJWHealthComponent::GetHealthPercentage() const
{
	check(MaxHealth > 0.f)
	return Health / MaxHealth;
}

void UJWHealthComponent::SetHealth(float InHealth)
{
	Health = InHealth;
	OnHealthValueChanged.Broadcast();
}

void UJWHealthComponent::SetMinHealth(float InMinHealth)
{
	MinHealth = InMinHealth;
	OnHealthValueChanged.Broadcast();
}

void UJWHealthComponent::SetMaxHealth(float InMaxHealth)
{
	MaxHealth = InMaxHealth;
	OnHealthValueChanged.Broadcast();
}

void UJWHealthComponent::DegreaseHealth(float DegreaseValue)
{
	Health = FMath::Clamp<float>(Health - DegreaseValue, MinHealth, MaxHealth);
	OnHealthValueChanged.Broadcast();
}


