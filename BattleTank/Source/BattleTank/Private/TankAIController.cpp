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
		auto AimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();

		// Aim at player
		AimComp->AimAt(PlayerTank->GetActorLocation());

		// Fire when in range
		// if (DistanceToTarget < AimComp->FiringRange)
		if (AimComp->GetFiringState() == EFiringState::Locked)
		{
			AimComp->Fire();
		}
	}
}
