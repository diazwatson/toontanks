// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"


void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController != nullptr)
		{
			ToonTanksPlayerController->SetPlayerEnableState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;

		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowersCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
		                                                             &AToonTanksPlayerController::SetPlayerEnableState,
		                                                             true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
	}
}

int32 AToonTankGameMode::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}
