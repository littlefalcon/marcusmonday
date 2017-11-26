// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterWeapons.generated.h"

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

private:
	//Set Weapon Mechanic
	UPROPERTY(EditAnywhere)
		EWeaponMechanic WeaponMechanic;

	// Set base damage
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int fireDamage = 50;

	// Set Rate of Fire (per minute)
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int fireRate = 500;

	// Set Magazine Capacity
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int magazineCapacity = 10;

	// Set Battery Consome per one time fire (
	UPROPERTY(EditAnywhere, Category = "Weapon Modify Panel")
		int batteryConsume = 2;

	

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

	//Charge Points can be stacked for complete charge and do more damage
	UPROPERTY(VisibleAnywhere, Category = "Weapon Debug")
		float chargePoints = chargeTime / maxCharge;

	// Calculated Battery Consume per Magazine
	UPROPERTY(VisibleAnywhere, Category = "Weapon Debug")
		int batteryCapacity = magazineCapacity * batteryConsume;
};
