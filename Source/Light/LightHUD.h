// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LightUserWidget.h"
#include "GameFramework/HUD.h"
#include "LightHUD.generated.h"

/**
 * 
 */
UCLASS()
class LIGHT_API ALightHUD : public AHUD
{
	GENERATED_BODY()

public:
	ALightHUD();

	class ULightUserWidget* HUDWidget;
	TSubclassOf<class UUserWidget> HUDWidgetClass;
};
