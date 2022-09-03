// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "LightUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LIGHT_API ULightUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	// 任务提示UI
	UVerticalBox* VerticalBoxMissionTips;

	// 操作提示UI
	UVerticalBox* VerticalBoxActionTips;
};
