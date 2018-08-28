// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoRemaining <= 0)
	{
		FiringState = EFiringState::Empty;
	}
	else if (Barrel->IsReloading())
	{
		FiringState = EFiringState::Reloading;
	}
	else if (isBarrelMoving)
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	// ...
}


void UTankAimingComponent::InitialiseAiming(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	FVector LaunchVelocity;
	auto LaunchLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate LaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
												(
													this,
													LaunchVelocity,
													LaunchLocation,
													HitLocation,
													Barrel->LaunchSpeed,
													false,
													0,
													0,
													ESuggestProjVelocityTraceOption::DoNotTrace
												);
	if (bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();

		// Move Barrel
		isBarrelMoving = MoveBarrelTowards(AimDirection);
	}

}

bool UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Subtract aim Rotation from current Rotation for Delta Rotation
	auto CurrentRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - CurrentRotation;


	Barrel->Elevate(DeltaRotation.Pitch);

	// Always yaw shortest direction
	if (FMath::Abs(DeltaRotation.Yaw) > 180) Turret->RotateTurret(-DeltaRotation.Yaw);
	else Turret->RotateTurret(DeltaRotation.Yaw);

	auto BFV = Barrel->GetForwardVector();
	return !BFV.Equals(AimDirection, .02f);
}

void UTankAimingComponent::Fire()
{
	if (AmmoRemaining <= 0) { return; }
	AmmoRemaining--;
	Barrel->Fire();
}

