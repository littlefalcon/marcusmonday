// Copyright (c) 2017 LittleFalcon.

#include "FireMechanicAuto.h"


// Sets default values for this component's properties
UFireMechanicAuto::UFireMechanicAuto()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UFireMechanicAuto::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UFireMechanicAuto::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsHoldingThisWeapon) {
		UE_LOG(LogTemp, Warning, TEXT("ready to fire"));
	}
	
	// ...
}


