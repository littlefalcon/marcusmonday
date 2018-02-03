// Copyright (c) 2017 LittleFalcon.

#include "MasterWeapons.h"
#include "FireMechanicAuto.h" // Handle Automatic Mechanic for Weapon
#include "FireMechanicBeam.h" // Handle Beam Mechanic for Weapon
#include "FireMechanicCharge.h" // Handle Charge Mechanic for Weapon
#include "Animation/AnimInstance.h" // Handle SkeletalMesh
#include "Kismet/GameplayStatics.h" //Handle Particle / Sound
#include "SpaceHorrorProjectile.h" //Handle Projectile Bullet /TODO make this class itself
#include "Runtime/Engine/Classes/Particles/Emitter.h" // beam weapon


// Sets default values
AMasterWeapons::AMasterWeapons(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Create Inherit Class TODO Create Inherit Class to same with Weapontype
	FireMechanicAuto = CreateDefaultSubobject<UFireMechanicAuto>(FName("FireMechanicAuto"));
	FireMechanicBeam = CreateDefaultSubobject<UFireMechanicBeam>(FName("FireMechanicBeam"));
	//TODO Set only player see 
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetOnlyOwnerSee(true);		// only the owning player will see this mesh
	Weapon->bCastDynamicShadow = false;
	Weapon->CastShadow = false;

}

// Called when the game starts or when spawned
void AMasterWeapons::BeginPlay()
{
	Super::BeginPlay();
	
	if (BP_Beam != nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Beam Found"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Beam Not Found"));
	}

	//Attach to BP_FirstPersonCharacter
	//attach
	//Check what weapon mechanic in this instance
	updateWeaponMechanic(WeaponMechanic);
	
	currentAmmo = magazineCapacity; //TODO sync to upgrade class
	uCurrentAmmo = currentAmmo;
	uMaxAmmo = currentBattery;
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
		UE_LOG(LogTemp, Log, TEXT("(%s)WP - Beam"), *GetName());
		FireMechanicAuto->IsHoldingThisWeapon = false;
		break;
	case EWeaponMechanic::SEMI:
		if (FireMechanicAuto != nullptr) {
			UE_LOG(LogTemp, Log, TEXT("(%s)WP - SemiAutomatic"), *GetName());
			FireMechanicAuto->IsHoldingThisWeapon = true;
			FireMechanicAuto->bSemiMechanic = true;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("(%s)WP - SemiAutomatic NOT FOUND"), *GetName());
		}
		break;
	case EWeaponMechanic::AUTO:
		if (FireMechanicAuto != nullptr) {
			UE_LOG(LogTemp, Log, TEXT("(%s)WP - Automatic"));
			FireMechanicAuto->IsHoldingThisWeapon = true;
			FireMechanicAuto->bSemiMechanic = false;
		}else{
			UE_LOG(LogTemp, Error, TEXT("(%s)WP - Automatic NOT FOUND"),*GetName());
		}
		break;
	case EWeaponMechanic::CHRG:
		UE_LOG(LogTemp, Warning, TEXT("(%s)WP - Charge"), *GetName());
		break;
	}
}

///FUNCTION
void AMasterWeapons::soundFire() {
	if (muzzleParticle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("muzzleParticle Not Assign!"));
	}
	if (Weapon == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Weapon Not Assign!"));
	}
	if (weaponSound == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("weaponSound Not Assign!"));
	}

	if (muzzleParticle != nullptr && Weapon != nullptr && weaponSound != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, weaponSound, Weapon->GetSocketLocation(TEXT("Muzzle")), 1, 1, 0, nullptr, nullptr);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Some Actor Not Assign!"));
	}
}

void AMasterWeapons::spawnParticleMuzzle()
{
	if (muzzleParticle != nullptr && Weapon != nullptr && weaponSound != nullptr) {
		UGameplayStatics::SpawnEmitterAtLocation(this, muzzleParticle, Weapon->GetSocketLocation(TEXT("Muzzle")), FRotator::ZeroRotator, FVector::OneVector, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Some Actor Not Assign!"));
	}
	
}

void AMasterWeapons::EsetCurrentAmmo(int NewAmmo) {
	setCurrentAmmo(NewAmmo);
}

void AMasterWeapons::spawnProjectileBullet() {
	if (Weapon == nullptr) { return; }
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			FRotator SpawnRotation = Weapon->GetSocketRotation(TEXT("Muzzle"));
			//SpawnRotation. += 90;
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = (this->GetActorForwardVector() * 2000) + Weapon->GetSocketLocation(TEXT("Muzzle"));;
			const FVector SpawnLocation = Weapon->GetSocketLocation(TEXT("Muzzle"));
			//const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			// spawn the projectile at the muzzle
			World->SpawnActor<ASpaceHorrorProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void AMasterWeapons::decreaseAmmo(int amount) { //TODO Clamp amount
	if (currentAmmo == 0) {
		return;
	}
	else
	{
		currentAmmo -= amount;
		uCurrentAmmo = currentAmmo;
	}
}

void AMasterWeapons::inceaseAmmo(int amount) {
	currentAmmo += amount;
	uCurrentAmmo = currentAmmo;
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
	uMaxAmmo = newcurrentbattery; 
	currentBattery = newcurrentbattery;
}

void AMasterWeapons::setCurrentAmmo(int newcurrentammo)
{
	currentAmmo = newcurrentammo;
}
///Get Method

int AMasterWeapons::getWeaponSlot(){
	return weaponSlot;
}

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


FVector AMasterWeapons::getWeaponMuzzlePosition() {
	if (Weapon == nullptr) { return FVector(0); }
	return Weapon->GetSocketLocation(TEXT("Muzzle"));
}

FVector AMasterWeapons::getWeaponForward() {
	return Weapon->GetForwardVector();
}





