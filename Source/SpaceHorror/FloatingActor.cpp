// Copyright (c) 2017 LittleFalcon.

#include "FloatingActor.h"


// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(PlayTime + DeltaTime) - FMath::Sin(PlayTime));
	NewLocation.Z += DeltaHeight * 20.0f;
	PlayTime += DeltaTime;
	SetActorLocation(NewLocation);
}

