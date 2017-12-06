// Copyright (c) 2017 LittleFalcon.

#include "MasterWeapons.h"
#include "FireMechanicAuto.h"

// Sets default values
AMasterWeapons::AMasterWeapons(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Inherit Class TODO Create Inherit Class to same with Weapontype
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

///FUNCTION
void AMasterWeapons::DecreaseAmmo(int amount) {
	if (currentAmmo == 0) {
		return;
	}
	else
	{
		currentAmmo -= amount;
	}
}

bool AMasterWeapons::IsAmmoDepleted() {
	if (currentAmmo == 0) {
		return true;
	}
	else
	{
		return false;
	}
}

///Set Method 

void AMasterWeapons::setCurrentBattery(int newcurrentbattery)
{
	currentBattery = newcurrentbattery;
}

void AMasterWeapons::setCurrentAmmo(int newcurrentammo)
{
	currentAmmo = newcurrentammo;
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

EWeaponMechanic AMasterWeapons::getWeaponMechanic() {
	return WeaponMechanic;
}





