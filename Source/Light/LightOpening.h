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
		UStaticMeshComponent* StaticMeshLightOpening;	// ��̬�����壬ֱ�Ӷ�ȡ����ģ��
	UPROPERTY()
		class UBoxComponent* BoxComponent;	// ��ײ��Χ��
	UPROPERTY()
		TArray<APlatLight*> ObjectArray; // �洢���еĵ�
	UPROPERTY()
		ADoor* ObjectDoor; // �洢��

	bool PlatLightNextState;
	bool OpenDoor;

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

	// ���ƹصƺ���
	UFUNCTION()
		void LightChange();
};
