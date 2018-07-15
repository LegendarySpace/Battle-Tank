// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"


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

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector LaunchVelocity;
	auto LaunchLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate LaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
												(
													this,
													LaunchVelocity,
													LaunchLocation,
													HitLocation,
													LaunchSpeed,
													false,
													0,
													0,
													ESuggestProjVelocityTraceOption::DoNotTrace
												);
	if (bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Firing Direction %s"), *AimDirection.ToString());

		// Move Barrel
	}

}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Subtract aim Rotation from current Rotation for Delta Rotation
	auto CurrentRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - CurrentRotation;

		// Gradually apply rotation to pitch and yaw (Each it's own gimbal)
	// Possibly return value if Firing Rotation == current Rotation
}
