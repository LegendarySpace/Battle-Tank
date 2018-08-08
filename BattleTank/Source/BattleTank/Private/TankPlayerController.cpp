// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

ATankPlayerController::ATankPlayerController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComp)
	{
		FoundAimingComponent(AimingComp);
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshairs();
}

void ATankPlayerController::AimTowardsCrosshairs()
{
	if (!GetPawn()) { return; }

	FVector	HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}
}

// Get world position of line trace through crosshairs, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(CrosshairRelativeX * ViewportSizeX, CrosshairRelativeY * ViewportSizeY);

	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection)) 
	{
	
		return GetLookVectorHitDirection(LookDirection, HitLocation);
	}
	return false;
}

// Deproject the screenpostion of the cursor to world position
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraLocation;
	if (!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection))
	{
		return false;
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitDirection(FVector LookDirection, FVector& HitLocation) const
{
	// Could just as easily used CameraLocation if it had been outted with LookDirection
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();

	// Line trace along the Look direction and check for collision
	// Convert firing range into meters then go out along look direction
	FVector TraceEnd = (LookDirection * (100 * GetPawn()->FindComponentByClass<UTankAimingComponent>()->FiringRange)) + CameraLocation;
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;

		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false;
}
