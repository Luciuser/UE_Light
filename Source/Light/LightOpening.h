// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatLight.h"
#include "Door.h"
#include "LightOpening.generated.h"

UCLASS()
class LIGHT_API ALightOpening : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightOpening();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshLightOpening;	// 静态网格体，直接读取开关模型
	UPROPERTY()
		class UBoxComponent* BoxComponent;	// 碰撞包围盒
	UPROPERTY()
		TArray<APlatLight*> ObjectArray; // 存储所有的灯
	UPROPERTY()
		ADoor* ObjectDoor; // 存储门

	bool PlatLightNextState;
	bool OpenDoor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 碰撞函数
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 开灯关灯函数
	UFUNCTION()
		void LightChange();
};
