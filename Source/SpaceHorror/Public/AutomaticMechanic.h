// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "MasterWeapons.h"
#include "AutomaticMechanic.generated.h"

/**
 * 
 */
UCLASS()
class AAutomaticMechanic : public AMasterWeapons
{
	GENERATED_BODY()
	
public:
	AAutomaticMechanic();

	virtual void Tick(float DeltaTime) override;

	void OnAutomaticFire();
};
