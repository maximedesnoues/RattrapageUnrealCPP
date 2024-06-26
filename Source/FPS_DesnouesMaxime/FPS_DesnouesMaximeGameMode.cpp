// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_DesnouesMaximeGameMode.h"
#include "FPS_DesnouesMaximeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPS_DesnouesMaximeGameMode::AFPS_DesnouesMaximeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
