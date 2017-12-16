// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireMechanicBeam.generated.h"

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

	void BeamMechanic();
	
};
