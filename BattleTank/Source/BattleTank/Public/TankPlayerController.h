// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UTankAimingComponent;
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Tank | Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Tank | Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
	// Cursor location in screen relation from upper left
	UPROPERTY(EditDefaultsOnly)
	float CrosshairRelativeY = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairRelativeX = .5f;


public:
	ATankPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

	// Begin barrel movement to target aimed at location
	void AimTowardsCrosshairs();

	bool GetSightRayHitLocation(FVector&) const;

	bool GetLookDirection(FVector2D, FVector&) const;

	bool GetLookVectorHitDirection(FVector, FVector&) const;
	
};
