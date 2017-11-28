// Copyright (c) 2017 LittleFalcon.

#include "FireMechanicAuto.h"
#include "MasterWeapons.h"
#include "SpaceHorrorCharacter.h"


// Sets default values for this component's properties
UFireMechanicAuto::UFireMechanicAuto()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Get Parent Class
	MasterWeapons = (AMasterWeapons*)this->GetOwner();

	//Get Player Character
	//SpaceHorrorCharacter = GetWorld()->GetFirstPlayerController()->GetComponentByClass(A//GetWorld()->GetFirstPlayerController()->GetCharacter();
	//SpaceHorrorCharacter = (ASpaceHorrorCharacter*)this->GetWorld()->GetFirstPlayerController()->GetCharacter();
	

}

void UFireMechanicAuto::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("damage = %f"), MasterWeapons->getBaseDamage());

	//Get fireRate
	fireRate = MasterWeapons->getFireRate();
	//Convert fireRate per minute to second
	fireRate = ConvertFireRate(fireRate);

	//Get Reload Time
	reloadTime = MasterWeapons->getReloadTime();
}


void UFireMechanicAuto::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsHoldingThisWeapon) {
		
		//Fire Mechanic
		if (canFire && IsPressFire) {
			Fire();
			canFire = false;
		}
		
		if (!canFire) {
			firedTimeCount += DeltaTime;
			if (firedTimeCount > fireRate && !MasterWeapons->IsAmmoDepleted()) {
				canFire = true;
			}
		}

		//Reload
		if (IsReloading) {
			reloadTime -= DeltaTime;
			UE_LOG(LogTemp, Warning, TEXT("Reloading %f"),reloadTime);
			if (reloadTime <= 0) {
				FinishReload();
				reloadTime = MasterWeapons->getReloadTime();

			}
		}
	}

}

void UFireMechanicAuto::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("firing"));
	IsPressFire = true;
	//Spawn Bullet
	//Muzzle Particle
	//Fire Animation
	//Fire Sound
	MasterWeapons->DecreaseAmmo(1);
}

float UFireMechanicAuto::ConvertFireRate(float firerate) {
	return 60/firerate;
}

void UFireMechanicAuto::PerformReload() {
	if (MasterWeapons->getCurrentAmmo() == MasterWeapons->getMagazineCapacity()){return;}
	IsReloading = true;
	//Wait Reload Animation Complete

}

void UFireMechanicAuto::FinishReload() {
	//find how much bullet need to regain
	int ammoCost = MasterWeapons->getMagazineCapacity() - MasterWeapons->getCurrentAmmo();
	// multiplier with batteryconsume
	ammoCost = ammoCost * MasterWeapons->getBatteryConsume();
	// decease battery from inventory
	int deceaseBattery = MasterWeapons->getCurrentBattery() - ammoCost;
	// set new current battery to inventory
	MasterWeapons->setCurrentBattery(deceaseBattery);
	// exit IsReloading loop
	IsReloading = false;
}



