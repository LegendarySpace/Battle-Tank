// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"



ATankPlayerController::ATankPlayerController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshairs();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshairs()
{
	if (!GetControlledTank()) { return; }

	FVector	HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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
	
		GetLookVectorHitDirection(LookDirection, HitLocation);


		return true;
	}
	return false;
}

// Deproject the screenpostion of the cursor to world position
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraLocation;
	if (!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection))
	{
		UE_LOG(LogTemp, Error, TEXT("Error Deprojecting crosshairs"));
		return false;
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitDirection(FVector LookDirection, FVector& HitLocation) const
{
	// Could just as easily used CameraLocation if it had been outted with LookDirection
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();

	// Line trace along the Look direction and check for collision
	FVector TraceEnd = (LookDirection * (100 * FiringRange)) + CameraLocation;		// Convert firing range into meters then go out along look direction
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;

		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false;
}
