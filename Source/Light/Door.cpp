// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���صľ�̬������
	StaticMeshDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshDoor"));
	//StaticMeshFire->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Main/Mesh/SM_Door.SM_Door"));	// ��ȡ��̬��������Դ
	if (CubeVisualAsset.Succeeded())
	{
		StaticMeshDoor->SetStaticMesh(CubeVisualAsset.Object);
		StaticMeshDoor->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::DoorOpen()
{
	// ���Ŵ���
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	NewRotation.Yaw -= 90;

	SetActorLocationAndRotation(NewLocation, NewRotation);	// ����λ�ü���ת
}

