// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float YawChange = RelativeSpeed * MaxRotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto CookedYaw = FMath::Clamp<float>(YawChange, -180, 180);

	AddRelativeRotation(FRotator(0, CookedYaw, 0));
}
