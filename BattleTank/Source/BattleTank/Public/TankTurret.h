// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), hidecategories = ("Collision", "Physics"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Turret)
	float MaxRotationDegreesPerSecond = 20;

	void RotateTurret(float RelativeSpeed);
	
};
