// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	FTankDelegate OnDeath;


	UPROPERTY(EditDefaultsOnly, Category = "Health")
	bool CanRegenerate = false;

	// Health Per Second
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 RegenAmount = 5;

	// Damage free seconds before health regen
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float HEALTH_REGEN_TIME = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	// Returns percent health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercentage() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TimeLastHit = 0;

private:
	float RegenCarryOver = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//  Engine called damage event
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Regen Life/Shields
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void Regen(float DeltaTime);

	/**
	*	TODO
	*	Lock Tank movement to 2 dimensions
	*	(Prevent Force being applied in unintended directions)
	**/
};
