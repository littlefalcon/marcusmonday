// Copyright (c) 2017 LittleFalcon.

#include "FireMechanicAuto.h"
#include "MasterWeapons.h"

// Sets default values for this component's properties
UFireMechanicAuto::UFireMechanicAuto()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Get parent class
	MasterWeapons = (AMasterWeapons*)this->GetOwner();

}

void UFireMechanicAuto::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("damage = %f"), MasterWeapons->getBaseDamage());
}


void UFireMechanicAuto::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsHoldingThisWeapon) {
		UE_LOG(LogTemp, Warning, TEXT("ready to fire"));
		
		if (canFire && IsPressFire) {
			Fire();
			canFire = false;
		}
		
		if (!canFire) {
			firedTimeCount += DeltaTime;
			if (firedTimeCount > fireRate) {
				canFire = true;
			}
		}
	}
	
}

void UFireMechanicAuto::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("firing"));
	//Spawn Bullet
	//Muzzle Particle
	//Fire Animation
	//Fire Sound
	

}



