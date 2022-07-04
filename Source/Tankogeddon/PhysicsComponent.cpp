// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsComponent.h"

// Sets default values for this component's properties
UPhysicsComponent::UPhysicsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPhysicsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPhysicsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FVector> UPhysicsComponent::GenerateTrajectory(FVector StartPos, FVector
	Velocity, float MaxTime, float TimeStep, float MinZValue)
{
	TArray<FVector> trajectory;
	FVector gravityVector(0, 0, Gravity);
	for (float time = 0; time < MaxTime; time = time + TimeStep)
	{
		FVector position = StartPos + Velocity * time + gravityVector * time * time /
			2;
		if (position.Z <= MinZValue)
			break;
		trajectory.Add(position);
	}
	return trajectory;
}