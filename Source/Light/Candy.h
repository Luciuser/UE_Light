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
		UStaticMeshComponent* StaticMeshRoot;	// ���ڵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshFire;	// ��̬�����壬ֱ�Ӷ�ȡ��ͼ�е�Բ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UPointLightComponent* PointLight;	// ���Դ�����ֱ�Ӷ�ȡ��ͼ�еĵ��Դ
	UPROPERTY()
		class UBoxComponent* BoxComponent;	// ��ײ��Χ��

private:
	bool LightOpenNext;	// �����һ�������״̬

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ��ײ����
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// �����ȼ/Ϩ����
	UFUNCTION()
		void LightChange();
};
