// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankTrack;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// TODO: Limit AI by FiringRange
	// Range in meters
	UPROPERTY(EditDefaultsOnly)
	int32 FiringRange = 10000;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Tank | Setup")
	virtual void InitialiseComponents(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet, UTankTrack* LeftTrack, UTankTrack* RightTrack);

	virtual void AimAt(FVector HitLocation);

	// The barrel handles firing		TODO: May remove barrel component and just call Barrel through aimComponent
	UFUNCTION(BlueprintCallable, Category = "Tank")
	virtual void Fire();
	
};
