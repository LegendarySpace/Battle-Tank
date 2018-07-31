// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


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

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank)
	{
		// Move towards Player
		MoveToActor(PlayerTank, AcceptanceRadius);

		// Aim at player
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());

		// Fire when in range
		// FiringRange = ControlledTank->Barrel->LaunchSpeed;
		// if (DistanceToTarget < FiringRange)
		if (false)
		{
			GetPawn()->FindComponentByClass<UTankAimingComponent>()->Fire();
		}
	}
}
