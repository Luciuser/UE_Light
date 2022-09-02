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

	// �۹�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpotBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpotLightComponent* SpotLight;	// �۹�������ֱ�Ӷ�ȡ��ͼ�еľ۹��

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
