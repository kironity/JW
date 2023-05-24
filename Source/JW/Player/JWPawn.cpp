// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JWPawn.h"

#include "JW.h"
#include "Components/JWHealthComponent.h"
#include "Kismet/GameplayStatics.h"

AJWPawn::AJWPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UJWHealthComponent>(L"HealthComponent");
}

void AJWPawn::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnReceiveAnyDamage);
	check(HealthComponent)
}

void AJWPawn::OnReceiveAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                                 class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || !IsAlive()) return;

	ApplyActualDamage(Damage);
}

void AJWPawn::ApplyActualDamage(float Damage)
{
	HealthComponent->DegreaseHealth(Damage);

	if (CanDie())
	{
		Die();
	}
}

void AJWPawn::Die()
{
	bIsDying = true;
	if (Cast<APlayerController>(GetController()))
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(Cast<APlayerController>(GetController()));
	}

	OnPlayerDeath.Broadcast();
	SetActorTickEnabled(false);
	UE_LOG(LogJW, Log, TEXT("Die: %s"), *GetName());
	Destroy();
}

bool AJWPawn::CanDie() const
{
	return HealthComponent->GetHealth() <= HealthComponent->GetMinHealthValue() && !bIsDying;
}

bool AJWPawn::IsAlive() const
{
	return HealthComponent->GetHealth() > HealthComponent->GetMinHealthValue() && !bIsDying;
}
