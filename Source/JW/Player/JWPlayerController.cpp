// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JWPlayerController.h"

#include "JW.h"
#include "JWPawn.h"
#include "GameFramework/GameModeBase.h"

void AJWPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AJWPawn* PosessedPlayer = Cast<AJWPawn>(InPawn);
	PosessedPlayer->OnPlayerDeath.AddDynamic(this, &ThisClass::OnControlledPlayerDeath);
}

void AJWPlayerController::OnControlledPlayerDeath()
{
	RespawnPlayer();
}

void AJWPlayerController::RespawnPlayer()
{
	const AActor* ActorStart = GetWorld()->GetAuthGameMode()->FindPlayerStart(this);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AJWPawn* RespawnedPlayer = GetWorld()->SpawnActor<AJWPawn>(GetWorld()->GetAuthGameMode()->DefaultPawnClass, ActorStart->GetActorLocation(),
	                                                           ActorStart->GetActorRotation(), SpawnParameters);
	
	if (RespawnedPlayer)
	{
		Possess(RespawnedPlayer);
		UE_LOG(LogJW, Log, TEXT("Respawn , %s"), *RespawnedPlayer->GetName());
	}
}
