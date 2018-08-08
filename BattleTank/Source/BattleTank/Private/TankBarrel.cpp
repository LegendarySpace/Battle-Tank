// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Projectile.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move barrel proper distance for the frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawElevation = RelativeRotation.Pitch + ElevationChange;
	auto NewElevation = FMath::Clamp(RawElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}

void UTankBarrel::Fire()
{
	if (ProjectileBlueprint && !IsReloading())
	{
		LastFireTime = FPlatformTime::Seconds();
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			GetSocketLocation(FName("Projectile")), GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
	}

}

bool UTankBarrel::IsReloading()
{
	return (FPlatformTime::Seconds() - LastFireTime) < ReloadTime;
}
