// Copyright (c) 2017 LittleFalcon.

#include "AutomaticMechanic.h"

//wait for player press fire input 

//when holding fire continue fire

//

AAutomaticMechanic::AAutomaticMechanic() {
	PrimaryActorTick.bCanEverTick = true;
}

void AAutomaticMechanic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("tick"));
}

void AAutomaticMechanic::OnAutomaticFire() {
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
}



