// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireMechanicAuto.generated.h"

class AMasterWeapons;
class ASpaceHorrorCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEHORROR_API UFireMechanicAuto : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireMechanicAuto();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Handle SemiFire +hitscan
	void SemiHitscanMechanic(); //TODO make hitscanfire method

	//Han
	void HitscanFire();

	//Enable fire mechanic when true
	bool IsHoldingThisWeapon;

	//Fire Projectile Bullet
	void ProjectileFire();

	//Handle fire repeatable
	bool canFire = true;

	//Counting fired time
	float firedTimer;

	//Check is SemiMechanic
	bool bSemiMechanic = false;

private:

	//Weapon Information
	AMasterWeapons* MasterWeapons = nullptr;

	//Input Information / Camera Position
	ASpaceHorrorCharacter* SpaceHorrorCharacter = nullptr;
	
	//Method convert firerate
	float ConvertFireRate(float firerate);

	//Get Input
	void GetPlayerInputInformation();

	//Get Weapon Information
	void GetWeaponAttributes();

	//Update Dynamic Weapon Information everyframe
	void GetDynamicWeaponAttributes();

	//Automatic Fire Mechanic
	void AutomaticMechanic();

	//Semi Fire Mechanic
	void SemiMechanic();

	//Firerate Controller
	void FirerateControl(float DeltaTime);

	//Reload Mechanic
	void ReloadMechanic(float DeltaTime);

	//Perform reload activity
	void PerformReload();

	//Finish reload activity
	void FinishReload();

	//Weapon Slot Number
	int weaponSlot;

	//Player Input Variables
	bool IsReload;
	bool IsInputFireUp;
	bool IsInputFireDown;
	int currentWeapon;

	// Weapon Attributes
	float fireRate;
	int baseDamage;
	int magazineCapacity;
	int batteryConsume;
	int batteryCapacity;
	float reloadTime;
	float recoil;
	float control;
	int accuracy;
	int fireRange;
	
	// Weapon Dynamic Attributes
	int currentAmmo;
	int currentBattery;


};
