// Fill out your copyright notice in the Description page of Project Settings.


#include "LightOpening.h"
#include "Components\PointLightComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ALightOpening::ALightOpening()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���صľ�̬������
	StaticMeshFire = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshFire"));
	//StaticMeshFire->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Main/Mesh/SM_CornerFrame.SM_CornerFrame"));	// ��ȡ��̬��������Դ
	if (CubeVisualAsset.Succeeded())
	{
		StaticMeshFire->SetStaticMesh(CubeVisualAsset.Object);
		StaticMeshFire->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMeshFire->SetCollisionEnabled(ECollisionEnabled::NoCollision);	// �رվ�̬���������ײ
	}

	// ��ײ��Χ��
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(50, 100, 100));	// ��Χ�з�Χ
	BoxComponent->SetupAttachment(StaticMeshFire);
	BoxComponent->SetRelativeLocation(GetActorLocation()+FVector(0,100,0));	// ��Χ���뾲̬������λ��ͬһԭ��
	BoxComponent->SetCollisionProfileName("Trigger");


	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACandy::OnOverlapBegin);
	//BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACandy::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ALightOpening::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightOpening::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

