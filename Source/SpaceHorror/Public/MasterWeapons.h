// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterWeapons.generated.h"

class UFireMechanicAuto;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
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

	// decease ammo function
	void DecreaseAmmo(int amount);

	// check is no ammo in magazine
	bool IsAmmoDepleted();

	//GET METHOD
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
	
	//SET METHOD 
	
	
	// set new current battery in inventory
	void setCurrentBattery(int newcurrentbattery);//TODO move to inventory class

	// set new current ammo when reload complete
	void setCurrentAmmo(int newcurrentammo);

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
	//current amount of battery carrying in inventory
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int currentBattery = 9999;

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
