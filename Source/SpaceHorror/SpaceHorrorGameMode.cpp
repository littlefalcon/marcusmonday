// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpaceHorrorGameMode.h"
#include "SpaceHorrorHUD.h"
#include "SpaceHorrorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpaceHorrorGameMode::ASpaceHorrorGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/StaticContent/FirstPerson/FirstPersonCPP/Blueprints/FirstPersonCharacter")); 
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASpaceHorrorHUD::StaticClass();
}
