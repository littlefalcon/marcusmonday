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

	bool IsHoldingThisWeapon;

	void Fire();

	bool canFire = true;

	bool IsHoldingTrigger;

	bool IsPressFire;

	float firedTimeCount = 0;


private:

	//Weapon Information
	AMasterWeapons* MasterWeapons = nullptr;

	//Input Information
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
	void AutomaticMechanic(float DeltaTime);

	//Reload Mechanic
	void ReloadMechanic(float DeltaTime);

	//Perform reload activity
	void PerformReload();

	//Finish reload activity
	void FinishReload();

	//activate reload sequence
	//bool IsReloading;

	//Player Input Variables
	bool IsFire;

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

	//DEV TEMP
	//var checking for log 1 time if same number
	int logCurrentAmmo;

};
