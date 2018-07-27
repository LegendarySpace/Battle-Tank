// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


class AProjectile;

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	double LastFireTime = 0;

	double ReloadTime = 3;

public:

	UPROPERTY(EditDefaultsOnly, Category = Tank)
	float LaunchSpeed = 4000;	// TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category=Elevation)
	float MaxDegreesPerSecond = 5;

	UPROPERTY(EditDefaultsOnly, Category = Elevation)
	float MaxElevation = 35;

	UPROPERTY(EditDefaultsOnly, Category = Elevation)
	float MinElevation = 0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	void Elevate(float RelativeSpeed);
	
	void Fire();
};
