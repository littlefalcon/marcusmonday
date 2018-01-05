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
	
	//Wait for player input every frame
	GetPlayerInputInformation();

	//true if Player Currenty Holding this weapon
	if (IsHoldingThisWeapon) {
		//Allow fire if currentweaponslot same as this weaponslot
		if (currentWeapon == weaponSlot) { //start check wep
			//Update current ammo
			GetDynamicWeaponAttributes();

			//check hitscan mechanic
			if (MasterWeapons->IsHitScan) {
				SemiHitScan();
				UE_LOG(LogTemp, Warning, TEXT("SemiHitScan"));
			}
			else
			{
				SemiMechanic();
				AutomaticMechanic();
				UE_LOG(LogTemp, Warning, TEXT("A1utoFire"));
			}
			//Handle firerate
			FirerateControl(DeltaTime);

			//Handle Reload
			ReloadMechanic(DeltaTime);
		}//end check wep
	}
}

void UFireMechanicAuto::SemiHitScan() { // BUG cant double function
	if (IsInputFireUp) {
		if (canFire & IsInputFireDown) {
			if (IsReload) { return; };
			//HITSCANFIRE 
			IsPressFire = true;
			MasterWeapons->Pressed = true;
			//Spawn Bullet
			//MasterWeapons->spawnParticleMuzzle();
			//Fire Animation
			//Fire Sound
			//MasterWeapons->soundFire();
			//DeceaseAmmo
			MasterWeapons->decreaseAmmo(1);
			//Update Ammo to HUD/UI
			currentAmmo = MasterWeapons->getCurrentAmmo();
			UE_LOG(LogTemp, Warning, TEXT("currentAmmo = %d"), currentAmmo);
			//HITSCANFIRE
			canFire = false;
			UE_LOG(LogTemp, Warning, TEXT("AutoFire"));
			canFire = false;
			SpaceHorrorCharacter->IsFireInputUp = false;
			UE_LOG(LogTemp, Warning, TEXT("Hitfire"));
		}
	}
}

void UFireMechanicAuto::FirerateControl(float DeltaTime) {

	if (!canFire) {
		firedTimeCount += DeltaTime;
		//canfire if cooldown time more than firerate and ammo is left in magazine
		if (firedTimeCount > fireRate && !MasterWeapons->IsAmmoDepleted()) {
			canFire = true;
			firedTimeCount = 0;
		}
	}
}

void UFireMechanicAuto::AutomaticMechanic() {
	if (IsSemiMechanic) { return; } //return if semiautomatic gun
	
	if (canFire && IsInputFireDown) {
		//return if reloading
		if (IsReload) { return; };
			Fire();
			canFire = false;
			UE_LOG(LogTemp, Warning, TEXT("AutoFire"));
	}
}

void UFireMechanicAuto::SemiMechanic() {
	if (!IsSemiMechanic) { return; } //return if not semiautomatic gun
	
	//release fire it will can fire 
	if (IsInputFireUp) {
		if (canFire & IsInputFireDown) {
			if (IsReload) { return; };
			Fire();
			canFire = false;
			SpaceHorrorCharacter->IsFireInputUp = false;
			UE_LOG(LogTemp, Warning, TEXT("SemiFire"));
		}
	}
}

void UFireMechanicAuto::ReloadMechanic(float DeltaTime) {
	if (IsReload) {
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
	MasterWeapons->spawnProjectileBullet(); // TODO make it dynamic
	//Muzzle Particle
	MasterWeapons->spawnParticleMuzzle();
	//Fire Animation
	//Fire Sound
	MasterWeapons->soundFire();
	//DeceaseAmmo
	MasterWeapons->decreaseAmmo(1);
	
	//Update Ammo to HUD/UI
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
	//get current holding weapon
	currentWeapon = SpaceHorrorCharacter->WeaponSelecter;
	//TODO some need change to get method
	//Get FireInput Is Down?
	IsInputFireDown = SpaceHorrorCharacter->IsFire;
	//Get FireInput Is Up?
	IsInputFireUp = SpaceHorrorCharacter->IsFireInputUp;
	//Get IsReloading Sequencing?
	IsReload = SpaceHorrorCharacter->IsReload;
	

}

void UFireMechanicAuto::GetWeaponAttributes() {
	
	weaponSlot = MasterWeapons->getWeaponSlot();;

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
