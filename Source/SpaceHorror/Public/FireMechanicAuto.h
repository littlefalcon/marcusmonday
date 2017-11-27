// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireMechanicAuto.generated.h"


class AMasterWeapons;

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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsHoldingThisWeapon;

	void Fire();

	bool canFire;

	bool IsHoldingTrigger;

	bool IsPressFire;

	float fireRate;

	float firedTimeCount = 0;
	
		
};
