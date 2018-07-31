// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	// Called by pathfinding by AI
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Tank | Initialise")
	void InitialiseMovement(UTankTrack* LeftToSet, UTankTrack* RightToSet);

	UFUNCTION(BlueprintCallable, Category = "Tank | FBW")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Tank | FBW")
	void IntendTurnRight(float Throw);

};
