// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterItems.generated.h"

UCLASS()
class SPACEHORROR_API AMasterItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private :
	void FXItemfloatUpandDown(float DeltaTime);
	UPROPERTY(EditAnywhere)float HeightMultiplier = 20;
	UPROPERTY(EditAnywhere)bool Customfloatspeed = false;
	UPROPERTY(EditAnywhere)float floatspeed = 0.01;
	float RunningTime;
	
};
