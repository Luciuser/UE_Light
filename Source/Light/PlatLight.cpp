// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatLight.h"
#include "Components\SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlatLight::APlatLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ¾Û¹âµÆ
	SpotBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpotLightBoom"));
	SpotBoom->SetupAttachment(RootComponent);
	SpotBoom->TargetArmLength = 0.0f; // The camera follows at this distance behind the character	
	SpotBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight")); 
	//SpotLight->SetupAttachment(SpotBoom, USpringArmComponent::SocketName);
	SpotLight->SetupAttachment(RootComponent);
	SpotLight->SetVisibility(true);
	SpotLight->SetLightColor(FLinearColor(1, 1, 1, 1));
	SpotLight->SetIntensity(3000);
	SpotLight->SetOuterConeAngle(40);
}

// Called when the game starts or when spawned
void APlatLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

