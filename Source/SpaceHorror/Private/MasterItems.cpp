// Copyright (c) 2017 LittleFalcon.RunningTime

#include "MasterItems.h"


// Sets default values
AMasterItems::AMasterItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasterItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FXItemfloatUpandDown(DeltaTime);
}

void AMasterItems::FXItemfloatUpandDown(float DeltaTime)
{
	if (Customfloatspeed) { DeltaTime = floatspeed; }
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * HeightMultiplier;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

