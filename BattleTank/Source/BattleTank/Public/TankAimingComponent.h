// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	Empty
};

// Forward Declariations
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Aiming System")
	EFiringState FiringState = EFiringState::Reloading;

	// Called when the game starts
	virtual void BeginPlay() override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	bool isBarrelMoving = false;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseAiming(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	// TODO: Limit AI by FiringRange
	// Range in meters
	UPROPERTY(EditDefaultsOnly)
	int32 FiringRange = 10000;

	UPROPERTY(EditDefaultsOnly, Category = "Aiming System")
	int32 Ammo = 10;

	void AimAt(FVector HitLocation);
	
	bool MoveBarrelTowards(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = "Aiming System")
	void Fire();

	EFiringState GetFiringState() const { return FiringState; }

	UFUNCTION(BlueprintCallable, Category = "Aiming System")
	int32 GetAmmo() const { return Ammo; }

};
