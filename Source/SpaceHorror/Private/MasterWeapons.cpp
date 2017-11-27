// Copyright (c) 2017 LittleFalcon.

#include "MasterWeapons.h"
#include "FireMechanicAuto.h"

// Sets default values
AMasterWeapons::AMasterWeapons(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FireMechanicAuto = CreateDefaultSubobject<UFireMechanicAuto>(FName("FireMechanicAuto"));
	//FireMechanicAuto = this->GetOwner()->FindComponentByClass<UFireMechanicAuto>();
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

void AMasterWeapons::onFire(){

}

void AMasterWeapons::setAutomatic() {
	
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

// return fireDamage
float AMasterWeapons::getBaseDamage() {
	return fireDamage;
}

EWeaponMechanic AMasterWeapons::getWeaponMechanic() {
	return WeaponMechanic;
}

///Set Method

