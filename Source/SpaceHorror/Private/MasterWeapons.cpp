// Copyright (c) 2017 LittleFalcon.

#include "MasterWeapons.h"
#include "FireMechanicAuto.h"

// Sets default values
AMasterWeapons::AMasterWeapons(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Inherit Class
	FireMechanicAuto = CreateDefaultSubobject<UFireMechanicAuto>(FName("FireMechanicAuto"));
}

// Called when the game starts or when spawned
void AMasterWeapons::BeginPlay()
{
	Super::BeginPlay();
	//Check what weapon mechanic in this instance
	updateWeaponMechanic(WeaponMechanic);
}

// Called every frame
void AMasterWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Check Weapon Mechanic of this Weapon Blueprint
void AMasterWeapons::updateWeaponMechanic(EWeaponMechanic WeaponMechanic) {
	switch (WeaponMechanic)
	{
	case EWeaponMechanic::BEAM:
		UE_LOG(LogTemp, Warning, TEXT("WP - Beam"));
		break;
	case EWeaponMechanic::SEMI:
		UE_LOG(LogTemp, Warning, TEXT("WP - Semi-Auto"));
		break;
	case EWeaponMechanic::AUTO:
		if (FireMechanicAuto != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("WP - Automatic"));
			FireMechanicAuto->IsHoldingThisWeapon = true;
		}else{UE_LOG(LogTemp, Warning, TEXT("WP - Automatic NOT FOUND"));}
		break;
	case EWeaponMechanic::CHRG:
		UE_LOG(LogTemp, Warning, TEXT("WP - Charge"));
		break;
	}
}

///Get Method

int AMasterWeapons::getCurrentAmmo()
{
	return currentAmmo;
}

float AMasterWeapons::getFireRate()
{
	return fireRate;
}

// return fireDamage
int AMasterWeapons::getBaseDamage() {
	return fireDamage;
}

int AMasterWeapons::getMagazineCapacity()
{
	return magazineCapacity;
}

int AMasterWeapons::getBatteryConsume()
{
	return batteryConsume;
}

int AMasterWeapons::getBatteryCapacity()
{
	return batteryCapacity;
}

float AMasterWeapons::getReloadTime()
{
	return reloadTime;
}

float AMasterWeapons::getRecoil()
{
	return recoil;
}

float AMasterWeapons::getControl()
{
	return control;
}

int AMasterWeapons::getAccuracy()
{
	return accuracy;
}

int AMasterWeapons::getFireRange()
{
	return fireRange;
}

int AMasterWeapons::getCurrentBattery()
{
	return currentBattery;
}

void AMasterWeapons::setCurrentBattery(int newcurrentbattery)
{
	currentBattery = newcurrentbattery;
}

//get weapon mechanic
EWeaponMechanic AMasterWeapons::getWeaponMechanic() {
	return WeaponMechanic;
}


///Set Method


///Function
//decease current ammo
void AMasterWeapons::DecreaseAmmo(int amount) {
	if (currentAmmo == 0) {
		
	}
	else
	{
		currentAmmo -= amount;
	}
}

//is no ammo in magazine?
bool AMasterWeapons::IsAmmoDepleted() {
	if (currentAmmo == 0) {
		return true;
	}
	else
	{
		return false;
	}
}



