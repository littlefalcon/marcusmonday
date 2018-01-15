// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireMechanicBeam.generated.h"

class AMasterWeapons;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEHORROR_API UFireMechanicBeam : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireMechanicBeam();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//Weapon Information
	AMasterWeapons* MasterWeapons = nullptr;

	//Get Weapon Information
	void GetWeaponAttributes();

	//Update Dynamic Weapon Information everyframe
	void GetDynamicWeaponAttributes();

	//?
	void BeamMechanic();

	//Method convert firerate
	float ConvertFireRate(float firerate);

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
