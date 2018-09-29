// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Suspension.generated.h"

class UPhysicsConstraintComponent;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API ASuspension : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuspension();

	// Components
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		UPhysicsConstraintComponent* Constraint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		UStaticMeshComponent* Wheel = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupConstraint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

