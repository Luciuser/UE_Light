// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatLight.generated.h"

UCLASS()
class LIGHT_API APlatLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatLight();

	// 聚光灯组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpotBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpotLightComponent* SpotLight;	// 聚光灯组件，直接读取蓝图中的聚光灯

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
