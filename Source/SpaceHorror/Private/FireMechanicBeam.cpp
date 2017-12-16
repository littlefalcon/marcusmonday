// Copyright (c) 2017 LittleFalcon.

#include "FireMechanicBeam.h"

// Sets default values for this component's properties
UFireMechanicBeam::UFireMechanicBeam()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFireMechanicBeam::BeginPlay()
{
	Super::BeginPlay();
	//SpaceHorrorCharacter = Cast<ASpaceHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
	// ...
	
}


// Called every frame
void UFireMechanicBeam::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//Wait for input
	BeamMechanic();
}

void UFireMechanicBeam::BeamMechanic() {
	//Spawn Beam particle
		//get beamsource
		
		//find hitloc by linetrace
		//find 
	//deceaseammo
}


