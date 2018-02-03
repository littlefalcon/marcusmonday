// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterWeapons.generated.h"

class UFireMechanicAuto;
class UFireMechanicBeam;
class UFireMechanicCharge;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EWeaponMechanic : uint8
{
	BEAM 	UMETA(DisplayName = "Beam"),
	SEMI 	UMETA(DisplayName = "Semi Automatic"),
	AUTO    UMETA(DisplayName = "Full Automatic"),
	CHRG    UMETA(DisplayName = "Charge")
};

UCLASS()
class SPACEHORROR_API AMasterWeapons : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterWeapons();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skeletal)
		class USkeletalMeshComponent* Weapon = NULL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BeamParticle)
		class UChildActorComponent* BP_Beam = nullptr;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//E = Save Editor
	UFUNCTION(BlueprintCallable)
		void EsetCurrentAmmo(int NewAmmo);

	//TODO use get 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int uCurrentAmmo;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int uMaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Modify Panel")
		int weaponVariant;

	//current amount of battery carrying in inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Modify Panel")
	int currentBattery = 9999;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Set Weapon Mechanic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Modify Panel")
		EWeaponMechanic WeaponMechanic;

	//Get Weapon Type
	EWeaponMechanic getWeaponMechanic();
	void updateWeaponMechanic(EWeaponMechanic WeaponMechanic);

	// TODO should delete?
	UFireMechanicAuto* FireMechanicAuto = nullptr;

	UFireMechanicBeam* FireMechanicBeam = nullptr;

	UFireMechanicCharge* FireMechanicCharge = nullptr;

	// Tick for Hitscan bullet
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		bool IsHitScan;

	// check is no ammo in magazine
	bool IsAmmoDepleted();

	//GET METHOD
	int getWeaponSlot();

	int getCurrentAmmo();

	float getFireRate();

	int getBaseDamage();
	
	int getMagazineCapacity();

	int getBatteryConsume();

	int getBatteryCapacity();
	
	float getReloadTime();
	
	float getRecoil();

	float getControl();

	int getAccuracy();

	int getFireRange();

	int getCurrentBattery();

	//get weapon muzzle position
	FVector getWeaponMuzzlePosition();

	FVector getWeaponForward();

	//SET METHOD 
	// decease ammo function
	void decreaseAmmo(int amount);
	void inceaseAmmo(int amount);
	// set new current battery in inventory
	void setCurrentBattery(int newcurrentbattery);//TODO move to inventory class

	// set new current ammo when reload complete
	void setCurrentAmmo(int newcurrentammo);
	
	/** Projectile bullet to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Bullet")
		TSubclassOf<class ASpaceHorrorProjectile> ProjectileClass;

	// sound data
	UPROPERTY(EditAnywhere, Category = WeaponFX)
		USoundBase* weaponSound = nullptr;

	// particle data
	UPROPERTY(EditAnywhere, Category = WeaponFX)
		UParticleSystem* muzzleParticle = nullptr;

	void soundFire();

	void spawnParticleMuzzle();

	void spawnProjectileBullet();

private:

	///DYNAMIC VARIABLES
	//Current Ammo
	UPROPERTY(EditAnywhere, Category = "Current Weapon Status")
		int currentAmmo; //TODO make to Dynamic with upgrade class
		
	//Current Accuracy
	UPROPERTY(VisibleAnywhere, Category = "Current Weapon Status")
		float currentAccuracy;

	//Current Recoil
	UPROPERTY(VisibleAnywhere, Category = "Current Weapon Status")
		float currentRecoil;

	//Charge Points can be stacked for complete charge and do more damage
	UPROPERTY(VisibleAnywhere, Category = "Current Weapon Status")
		float chargePoints = chargeTime / maxCharge;

	///STATIC VARIABLES
	// Weapon Slot
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int weaponSlot;


	// Set base damage
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int fireDamage = 50;

	// Set Rate of Fire (per minute)
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int fireRate = 500;

	// Set Magazine Capacity
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int magazineCapacity = 10;

	// Set Battery Consome per fire
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int batteryConsume = 2;

	//TODO move to inventory class
	

	// Calculated Battery Consume per Magazine
	UPROPERTY(VisibleAnywhere, Category = "Weapon Modify Panel")
		int batteryCapacity = magazineCapacity * batteryConsume;


	// Set Reload Time (second)
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		float reloadTime = 3;

	// Set Recoil Rate (More rate more camera sway)
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		float recoil = 5;

	// Set Control Rate 0.3-0.9(More rate can suppress time before starting bullet sway)
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		float control = 1;
	
	// Set Accuracy Rate (More rate more bullet sway)
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int accuracy = 50;

	// Set max range of fire (meter) when out of range bullet won't do damage
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int fireRange = 80;

	///Projectile Bullet Mechanics Only ///
	//Bullet flight speed (Only for Projectile Bullet Mechanics)
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel|Projectile Bullet")
		int projectileSpeed = 50;
	///Projectile Bullet Mechanics Only ///

	///Charge Mechanics Only ///
	//Set Time to Complete Charge (second)
	UPROPERTY(EditAnywhere,Category = "Weapon Modify Panel|Charge Weapon")
		float chargeTime = 1;

	//Set Maximize Requirement for Complete Charge
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel|Charge Weapon")
		int maxCharge = 10;

	///Charge Mechanics Only ///
	
	/// METHOD
};
