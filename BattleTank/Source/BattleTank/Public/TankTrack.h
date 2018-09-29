// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class USpawnPoint;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Tank)
	float MaxForce = 1600000;

	float CurrentThrottle = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Suspension")
	USpawnPoint* FrontShock;

	UPROPERTY(EditDefaultsOnly, Category = "Suspension")
	USpawnPoint* MidShock;

	UPROPERTY(EditDefaultsOnly, Category = "Suspension")
	USpawnPoint* BackShock;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, Category = Tank)
	void SetThrottle(float Throttle);

	void DriveTrack();



};
