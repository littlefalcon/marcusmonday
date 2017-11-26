// Copyright (c) 2017 LittleFalcon.

#include "MasterWeapons.h"

// Sets default values
AMasterWeapons::AMasterWeapons()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (WeaponMechanic == EWeaponMechanic::AUTO) {
	}
}

// Called when the game starts or when spawned
void AMasterWeapons::BeginPlay()
{
	Super::BeginPlay();
	
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

//swtich weapon trigger

void AMasterWeapons::switchWeapon(FString weaponSlot) {

	//Get Weapon Type in Blueprint
	switch (WeaponMechanic)
	{
	case EWeaponMechanic::BEAM:
		break;
	case EWeaponMechanic::SEMI:
		break;
	case EWeaponMechanic::AUTO:
		break;
	case EWeaponMechanic::CHRG:
		break;
	}
}
///Get Method

// return fireDamage
float AMasterWeapons::getBaseDamage() {
	return fireDamage;
}

///Set Method

