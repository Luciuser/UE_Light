// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightGameMode.h"
#include "LightCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALightGameMode::ALightGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Main/Blueprints/PersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	CurrentCandy = nullptr;
}
