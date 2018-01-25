// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpaceHorrorCharacter.h"
#include "SpaceHorrorProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"

#include "MasterWeapons.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ASpaceHorrorCharacter

ASpaceHorrorCharacter::ASpaceHorrorCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);		// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->Hand = EControllerHand::Right;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
	DC_Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("DC_Gun"));
	DC_Gun->SetupAttachment(RootComponent);
	
	SA_GUN = CreateDefaultSubobject<UChildActorComponent>(TEXT("SA_Gun"));
	SA_GUN->SetupAttachment(RootComponent);

	B_Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("B_Gun"));
	B_Gun->SetupAttachment(RootComponent);
	
}

void ASpaceHorrorCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	
	//Attach Gun to Player BP
	DC_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	SA_GUN->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	B_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	
	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}

	DC_Gun->SetHiddenInGame(false, true);
	SA_GUN->SetHiddenInGame(false, true);
	B_Gun->SetHiddenInGame(false, true);

	//Default select weapon
	Weapon2();

	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASpaceHorrorCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASpaceHorrorCharacter::TouchStarted);
	if (EnableTouchscreenMovement(PlayerInputComponent) == false)
	{
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceHorrorCharacter::InputFireDown);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceHorrorCharacter::InputFireUp);
	}

	//Weapon Selecter TODO MAKE TO ENUM
	PlayerInputComponent->BindAction("Weapon 1", IE_Pressed, this, &ASpaceHorrorCharacter::Weapon1);
	PlayerInputComponent->BindAction("Weapon 2", IE_Pressed, this, &ASpaceHorrorCharacter::Weapon2);
	PlayerInputComponent->BindAction("Weapon 3", IE_Pressed, this, &ASpaceHorrorCharacter::Weapon3);
	PlayerInputComponent->BindAction("Weapon 4", IE_Pressed, this, &ASpaceHorrorCharacter::Weapon4);
	PlayerInputComponent->BindAction("Weapon 5", IE_Pressed, this, &ASpaceHorrorCharacter::Weapon5);
	PlayerInputComponent->BindAction("Weapon 6", IE_Pressed, this, &ASpaceHorrorCharacter::Weapon6);

	//Reload Action
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASpaceHorrorCharacter::Reload);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ASpaceHorrorCharacter::OnResetVR);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpaceHorrorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceHorrorCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpaceHorrorCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpaceHorrorCharacter::LookUpAtRate);

}

void ASpaceHorrorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MuzzleLocation = FP_MuzzleLocation->GetComponentLocation();

	
}

void ASpaceHorrorCharacter::Reload() {
	if (bMenuOpen) { return; }
	IsReload = true;
}

void ASpaceHorrorCharacter::setReload(bool setbool) {
	IsReload = setbool;
}

void ASpaceHorrorCharacter::InputFireDown()
{
	if (bMenuOpen) { return; }
	IsFire = true;
	IsFireInputDown = true;
}

void ASpaceHorrorCharacter::InputFireUp() {
	if (bMenuOpen) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Relase Fire"));
	IsFire = false;
	IsFireInputUp = true;
}

void ASpaceHorrorCharacter::Weapon1()
{
	if (WeaponSelecter != 0)
	{
		WeaponSelecter = 0;
		UE_LOG(LogTemp, Warning, TEXT("Select Door Cutter"));
		B_Gun->SetHiddenInGame(false, true);

		DC_Gun->SetHiddenInGame(true, true);
		SA_GUN->SetHiddenInGame(true, true);
		
	}
}

void ASpaceHorrorCharacter::Weapon2()
{
	if (WeaponSelecter != 1)
	{
		WeaponSelecter = 1;
		UE_LOG(LogTemp, Warning, TEXT("Select Gauss Rifle"));
		DC_Gun->SetHiddenInGame(false, true);
		
		SA_GUN->SetHiddenInGame(true, true);
		B_Gun->SetHiddenInGame(true, true);
	}
}

void ASpaceHorrorCharacter::Weapon3()
{
	
	if (WeaponSelecter != 2)
	{
		WeaponSelecter = 2;
		UE_LOG(LogTemp, Warning, TEXT("Select Force Gun"));
		SA_GUN->SetHiddenInGame(false, true);

		DC_Gun->SetHiddenInGame(true, true);
		B_Gun->SetHiddenInGame(true, true);

	}
}

void ASpaceHorrorCharacter::Weapon4()
{
	
	if (WeaponSelecter != 3)
	{
		WeaponSelecter = 3;
		UE_LOG(LogTemp, Warning, TEXT("Select Laser Gun"));
	}
}

void ASpaceHorrorCharacter::Weapon5()
{
	
	if (WeaponSelecter != 4)
	{
		WeaponSelecter = 4;
		UE_LOG(LogTemp, Warning, TEXT("Select Rail Gun"));
	}
}

void ASpaceHorrorCharacter::Weapon6()
{
	
	if (WeaponSelecter != 5)
	{
		WeaponSelecter = 5;
		UE_LOG(LogTemp, Warning, TEXT("Select Stun Gun"));
	}
}

void ASpaceHorrorCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASpaceHorrorCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ASpaceHorrorCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		//OnFire();
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void ASpaceHorrorCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void ASpaceHorrorCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ASpaceHorrorCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASpaceHorrorCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASpaceHorrorCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ASpaceHorrorCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASpaceHorrorCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ASpaceHorrorCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASpaceHorrorCharacter::TouchUpdate);
	}
	return bResult;
}


FVector ASpaceHorrorCharacter::getCameraComponentLocation() {
	return FirstPersonCameraComponent->GetComponentLocation();
}

FVector ASpaceHorrorCharacter::getCameraForwardVector() {
	return FirstPersonCameraComponent->GetForwardVector();
}

//
