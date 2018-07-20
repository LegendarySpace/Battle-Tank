// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


ATankAIController::ATankAIController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetPlayerTank())
	{
		// Move towards Player

		// Aim at player
		ATank* ControlledTank = Cast<ATank>(GetPawn());
		ControlledTank->AimAt(GetPlayerTank()->GetActorLocation());

		// Fire when in range
		// FiringRange = ControlledTank->Barrel->LaunchSpeed;
		// if (DistanceToTarget < FiringRange)
		if (true)
		{
			ControlledTank->Fire();
		}
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto PlayerTank = Cast<ATank>(Player);
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("First Player Controller is NOT a possessing a tank"));
		return nullptr;
	}
	return PlayerTank;
}
