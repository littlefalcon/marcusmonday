// Copyright (c) 2017 LittleFalcon.

#include "FireMechanicAuto.h"
#include "MasterWeapons.h"
#include "SpaceHorrorCharacter.h"

UFireMechanicAuto::UFireMechanicAuto()
{

	PrimaryComponentTick.bCanEverTick = true;

	//Get Parent Class
	MasterWeapons = (AMasterWeapons*)this->GetOwner();

}

void UFireMechanicAuto::BeginPlay()
{
	Super::BeginPlay();
	SpaceHorrorCharacter = Cast<ASpaceHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	GetWeaponAttributes();
}


void UFireMechanicAuto::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Update current ammo
	GetDynamicWeaponAttributes();
	//Wait for player input every frame
	GetPlayerInputInformation();
	//Handle Firing
	AutomaticMechanic(DeltaTime);
	//Handle Reload
	ReloadMechanic(DeltaTime);
	
}

void UFireMechanicAuto::AutomaticMechanic(float DeltaTime) {
	
	if (canFire && IsFire) {
		if (SpaceHorrorCharacter->IsReload) { return; };
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
}

void UFireMechanicAuto::ReloadMechanic(float DeltaTime) {
	if (SpaceHorrorCharacter->IsReload) {
		PerformReload();
		reloadTime -= DeltaTime;
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
	MasterWeapons->decreaseAmmo(1);
	currentAmmo = MasterWeapons->getCurrentAmmo();
	UE_LOG(LogTemp, Warning, TEXT("currentAmmo = %d"),currentAmmo);
}


void UFireMechanicAuto::PerformReload() {
	if (currentAmmo == magazineCapacity){
		SpaceHorrorCharacter->setReload(false);
		UE_LOG(LogTemp, Warning, TEXT("Magazine is full no need to reload"));
		return;
	}
}


void UFireMechanicAuto::FinishReload() {
	//find how much bullet need to regain
	int usedAmmo = magazineCapacity - currentAmmo;
	UE_LOG(LogTemp, Warning, TEXT("%d ammo need to regain"), usedAmmo);
	int ammoCost = usedAmmo;	
	// multiplier with batteryconsume
	ammoCost = ammoCost * batteryConsume;
	// decease battery from inventory
	int deceaseBattery = currentBattery - ammoCost;
	// set new current battery to inventory
	MasterWeapons->setCurrentBattery(deceaseBattery);
	UE_LOG(LogTemp, Warning, TEXT("BatteryConsume = %d"), ammoCost);
	// set new ammo in magazine
	MasterWeapons->inceaseAmmo(usedAmmo);
	// exit IsReloading loop
	SpaceHorrorCharacter->setReload(false);
	UE_LOG(LogTemp, Warning, TEXT("FinishReload CurrentAmmo = %d CurrentBattery = %d"), MasterWeapons->getCurrentAmmo(),MasterWeapons->getCurrentBattery());
}

void UFireMechanicAuto::GetPlayerInputInformation() {
	//Get Control Class Everyframe
	SpaceHorrorCharacter = Cast<ASpaceHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	//Get FireButton Input
	IsFire = SpaceHorrorCharacter->IsFire;
	//Get Reload Input
	//IsReloading = SpaceHorrorCharacter->IsReload;
}

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

void UFireMechanicAuto::GetDynamicWeaponAttributes() {

	currentAmmo = MasterWeapons->getCurrentAmmo();

	currentBattery = MasterWeapons->getCurrentBattery();

}


float UFireMechanicAuto::ConvertFireRate(float firerate) {
	return 60 / firerate;
}
