// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightOpening.generated.h"

UCLASS()
class LIGHT_API ALightOpening : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightOpening();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshFire;	// ��̬�����壬ֱ�Ӷ�ȡ����ģ��
	UPROPERTY()
		class UBoxComponent* BoxComponent;	// ��ײ��Χ��

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
