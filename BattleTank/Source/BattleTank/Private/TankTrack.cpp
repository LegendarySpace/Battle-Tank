// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SpawnPoint.h"


UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	FrontShock = CreateDefaultSubobject<USpawnPoint>(FName("Front Shock"));
	FrontShock->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	FrontShock->SetRelativeLocation(FVector(207, 0, 78));

	MidShock = CreateDefaultSubobject<USpawnPoint>(FName("Mid Shock"));
	MidShock->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	FrontShock->SetRelativeLocation(FVector(0, 0, 78));

	BackShock = CreateDefaultSubobject<USpawnPoint>(FName("Back Shock"));
	BackShock->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	FrontShock->SetRelativeLocation(FVector(-213, 0, 78));
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{
	// Get lateral speed
	auto LateralSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Determine lateral speed correction for frame
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto LateralCorrection = -LateralSpeed / DeltaTime * GetRightVector();

	// Calculate and apply lateral correction F = M A
	auto Root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectiveForce = (LateralCorrection * Root->GetMass()) / 2; // Two tracks
	Root->AddForce(CorrectiveForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto AppliedForce = GetForwardVector() * CurrentThrottle * MaxForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}


