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

	AMasterWeapons* MasterWeapons = nullptr;

	ASpaceHorrorCharacter* SpaceHorrorCharacter = nullptr;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsHoldingThisWeapon;

	void Fire();

	bool canFire = true;

	bool IsHoldingTrigger;

	bool IsPressFire;

	float firedTimeCount = 0;


private:

	float ConvertFireRate(float firerate);

	void GetPlayerInputInformation();

	void GetWeaponAttributes();

	void PerformReload();

	void FinishReload();

	//activate reload sequence
	bool IsReloading;

	//Player Input Variables
	bool IsFire;

	// Weapon Attributes
	int currentAmmo;

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

	int currentBattery;

	//DEV TEMP
	//var checking for log 1 time if same number
	int logCurrentAmmo;

};
