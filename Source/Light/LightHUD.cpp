// Fill out your copyright notice in the Description page of Project Settings.


#include "LightHUD.h"
#include "UObject/ConstructorHelpers.h"

ALightHUD::ALightHUD() {
	if (GEngine && GEngine->GameViewport)
	{
		// �ҵ���ͼ�࣬��Ҫ��_C
		static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetBP(TEXT("WidgetBlueprint'/Game/Main/HUD/BaseHUD.BaseHUD_C'"));
		if (HUDWidgetBP.Succeeded()) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Find the HUD."));
			HUDWidgetClass = HUDWidgetBP.Class; // �õ�class
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can not find the HUD."));
		}

		HUDWidget = CreateWidget<ULightUserWidget>(GetWorld()->GetGameInstance(), HUDWidgetClass);
		if (HUDWidget != nullptr) {
			HUDWidget->AddToViewport();	// ��ʾUI
		}
	}
}