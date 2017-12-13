// Copyright (c) 2017 LittleFalcon.

#include "FireMechanicCharge.h"


// Sets default values for this component's properties
UFireMechanicCharge::UFireMechanicCharge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFireMechanicCharge::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFireMechanicCharge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

