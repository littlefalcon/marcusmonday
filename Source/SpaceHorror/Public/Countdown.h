	// Copyright (c) 2017 LittleFalcon.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class SPACEHORROR_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	ACountdown();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)void CountdownHasFinished();

protected:
	virtual void BeginPlay() override;

private:	
	
	//How long, in seconds, the countdown will run
	UPROPERTY(EditAnywhere)int32 CountdownTime;

	class UTextRenderComponent* CountdownText;
	void UpdateTimerDisplay();

	void AdvanceTimer();

	
	virtual void CountdownHasFinished_Implementation(); //_Implementation mean you declare the parent of CountdownHasFinished that use in BP.s

	FTimerHandle CountdownTimerHandle;

};
