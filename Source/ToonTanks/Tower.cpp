// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (InFireRange())
	{
		// If in Range, rotate toward Tank
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		// If in Range, Fire
		Fire();
	}
}

bool ATower::InFireRange() const
{
	// Find the distance to the Tank
	if (Tank)
	{
		const float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		// Check to see if the Tank is in range
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
