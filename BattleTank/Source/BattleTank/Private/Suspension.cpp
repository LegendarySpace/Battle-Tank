// Fill out your copyright notice in the Description page of Project Settings.

#include "Suspension.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASuspension::ASuspension()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(Constraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Constraint);
	
}

// Called when the game starts or when spawned
void ASuspension::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
}

void ASuspension::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	Constraint->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASuspension::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

