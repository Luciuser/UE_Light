// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Candy.generated.h"

UCLASS()
class LIGHT_API ACandy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandy();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshRoot;	// 根节点
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshFire;	// 静态网格体，直接读取蓝图中的圆柱体
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UPointLightComponent* PointLight;	// 点光源组件，直接读取蓝图中的点光源
	UPROPERTY()
		class UBoxComponent* BoxComponent;	// 碰撞包围盒

private:
	bool LightOpenNext;	// 标记下一次蜡烛的状态

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

	// 蜡烛点燃/熄灭函数
	UFUNCTION()
		void LightChange();
};
