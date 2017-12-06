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
	//TODO LEARN CAST
	//SpaceHorrorCharacter = Cast<ASpaceHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
}

void UFireMechanicAuto::BeginPlay()
{
	Super::BeginPlay();
	
	SpaceHorrorCharacter = Cast<ASpaceHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	GetWeaponAttributes();
	fireRate = ConvertFireRate(fireRate);
}


void UFireMechanicAuto::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Get Control Class Everyframe
	SpaceHorrorCharacter = Cast<ASpaceHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	GetWeaponAttributes();
	//Wait for player input every frame
	GetPlayerInputInformation();

	//Fire Mechanic
	if (canFire && IsFire) {
		Fire();
		canFire = false;
	}
		
	if (!canFire) {
		firedTimeCount += DeltaTime;
		if (firedTimeCount > fireRate && !MasterWeapons->IsAmmoDepleted()) {
			canFire = true;
			firedTimeCount = 0;
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

void UFireMechanicAuto::Fire() {
	IsPressFire = true;
	//Spawn Bullet
	//Muzzle Particle
	//Fire Animation
	//Fire Sound
	MasterWeapons->DecreaseAmmo(1);
	currentAmmo = MasterWeapons->getCurrentAmmo();
	UE_LOG(LogTemp, Warning, TEXT("currentAmmo = %d"),currentAmmo);
	//DEV LOG
}

float UFireMechanicAuto::ConvertFireRate(float firerate) {
	return 60/firerate;
}

void UFireMechanicAuto::PerformReload() {
	if (currentAmmo == magazineCapacity){return;}
	IsReloading = true;
	//Wait Reload Animation Complete

}

void UFireMechanicAuto::GetPlayerInputInformation() {
	
	IsFire = SpaceHorrorCharacter->IsFire;
}

void UFireMechanicAuto::FinishReload() {
	//find how much bullet need to regain
	int ammoCost = magazineCapacity - currentAmmo;
	// multiplier with batteryconsume
	ammoCost = ammoCost * batteryConsume;
	// decease battery from inventory
	int deceaseBattery = currentBattery - ammoCost;
	// set new current battery to inventory
	MasterWeapons->setCurrentBattery(deceaseBattery);
	// exit IsReloading loop
	IsReloading = false;
}


// Get Weapon Attributes from MasterWeapon Class (Static Variable)
void UFireMechanicAuto::GetWeaponAttributes() {
	
	currentAmmo = MasterWeapons->getCurrentAmmo();

	fireRate = MasterWeapons->getFireRate();
	fireRate = ConvertFireRate(fireRate);

	baseDamage = MasterWeapons->getBaseDamage();

	magazineCapacity = MasterWeapons->getMagazineCapacity();

	batteryConsume = MasterWeapons->getBatteryConsume();

	batteryCapacity = MasterWeapons->getBatteryCapacity();

	reloadTime = MasterWeapons->getReloadTime();

	recoil = MasterWeapons->getRecoil();

	control = MasterWeapons->getControl();

	accuracy = MasterWeapons->getAccuracy();

	fireRange = MasterWeapons->getFireRange();

	currentBattery = MasterWeapons->getCurrentBattery();

}



