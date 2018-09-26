// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TimeLastHit = FPlatformTime::Seconds();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentHealth < StartingHealth) {
		if (FPlatformTime::Seconds() > (TimeLastHit + HEALTH_REGEN_TIME)) Regen(DeltaTime);
	}
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto AppliedDamage = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= AppliedDamage;

	TimeLastHit = FPlatformTime::Seconds();

	if (CurrentHealth <= 0) OnDeath.Broadcast();

	return AppliedDamage;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Regen(float DeltaTime)
{
	// TODO Use world delta instead of passing in
	RegenCarryOver = (5 * DeltaTime);
	if (RegenCarryOver > 1) {
		RegenCarryOver--;
		CurrentHealth++;
	}
}



