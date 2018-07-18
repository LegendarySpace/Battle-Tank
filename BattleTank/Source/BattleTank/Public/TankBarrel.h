// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


class AProjectile;

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision", "Physics"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Tank)
	float LaunchSpeed = 4000;	// TODO find sensible default

	UPROPERTY(EditAnywhere, Category=Elevation)
	float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Elevation)
	float MaxElevation = 35;

	UPROPERTY(EditAnywhere, Category = Elevation)
	float MinElevation = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	void Elevate(float RelativeSpeed);
	
	void Fire();
};
