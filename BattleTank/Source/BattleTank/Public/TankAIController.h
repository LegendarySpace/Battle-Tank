// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	ATankAIController();

	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.f;

};
