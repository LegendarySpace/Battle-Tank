// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


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
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("First Player Controller is NOT a possessing anything"));
		return nullptr;
	}
	return Cast<ATank>(PlayerTank);
}
