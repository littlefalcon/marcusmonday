// Copyright (c) 2017 LittleFalcon.

#include "FireMechanicBeam.h"
#include "MasterWeapons.h"
#include "DrawDebugHelpers.h" //TODO DELETE


// Sets default values for this component's properties
UFireMechanicBeam::UFireMechanicBeam()
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	//Get Parent Class
	MasterWeapons = (AMasterWeapons*)this->GetOwner();
	// ...
}


// Called when the game starts
void UFireMechanicBeam::BeginPlay()
{
	Super::BeginPlay();
	//SpaceHorrorCharacter = Cast<ASpaceHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
}


// Called every frame
void UFireMechanicBeam::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//Wait for input
	//BeamMechanic();
}

void UFireMechanicBeam::GetDynamicWeaponAttributes()
{
}

void UFireMechanicBeam::BeamMechanic() {
	if (MasterWeapons == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("MasterWeapon not found"));
		return;
	}
	FHitResult hit; //store hit object reference
	FColor traceColor = FColor::Red; //default trace color
	
	//bullet out position
	FVector startVector = MasterWeapons->getWeaponMuzzlePosition();
	//bullet move position (forward)
	FVector endVector = startVector + (MasterWeapons->getWeaponForward() * (fireRange * 1000));
	//return true if hit
	bool isHit = GetWorld()->LineTraceSingleByChannel(hit, startVector, endVector, ECollisionChannel::ECC_Visibility);

	if (isHit) {
		//set endVector to impactposition
		endVector = hit.ImpactPoint;
		if (hit.bBlockingHit) {
			if (hit.GetActor()) { //do if hit actor
				UE_LOG(LogTemp, Warning, TEXT("%s"), *hit.GetActor()->GetName());
				traceColor = FColor::Green;

			}
			else //do if hit not hit actor
			{
				UE_LOG(LogTemp, Error, TEXT(" Hit Other "));
				traceColor = FColor::Yellow;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Hit"));
			traceColor = FColor::Red;
		}

		//draw debug line when hit
		//DrawDebugLine(GetWorld(), hit.TraceStart, endVector, traceColor, false, 10.0f, 0, 10.0f);
	}


	//Spawn Beam particle
		//get beamsource
		
		//find hitloc by linetrace
		//find 
	//deceaseammo
}

float UFireMechanicBeam::ConvertFireRate(float firerate)
{
	return 60 / firerate;
}

void UFireMechanicBeam::GetWeaponAttributes() {

	weaponSlot = MasterWeapons->getWeaponSlot();;

	currentAmmo = MasterWeapons->getCurrentAmmo();

	fireRate = MasterWeapons->getFireRate();
	fireRate = ConvertFireRate(fireRate);

	baseDamage = MasterWeapons->getBaseDamage();

	magazineCapacity = MasterWeapons->getMagazineCapacity();

	batteryConsume = MasterWeapons->getBatteryConsume();

	batteryCapacity = MasterWeapons->getBatteryCapacity();

	reloadTime = MasterWeapons->getReloadTime();

	recoil = MasterWeapons->getRecoil();

	control = MasterWeapons->getControl();

	accuracy = MasterWeapons->getAccuracy();

	fireRange = MasterWeapons->getFireRange();

	currentBattery = MasterWeapons->getCurrentBattery();

}
