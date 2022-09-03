// Fill out your copyright notice in the Description page of Project Settings.


#include "LightUserWidget.h"

bool ULightUserWidget::Initialize() {
	Super::Initialize();

	VerticalBoxMissionTips = Cast<UVerticalBox>(GetWidgetFromName("VerticalBoxMission"));
	VerticalBoxActionTips = Cast<UVerticalBox>(GetWidgetFromName("VerticalBoxTips"));

	return true;
}