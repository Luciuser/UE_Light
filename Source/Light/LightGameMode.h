// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Candy.h"
#include "LightGameMode.generated.h"

UCLASS(minimalapi)
class ALightGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALightGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		ACandy* CurrentCandy;
};



