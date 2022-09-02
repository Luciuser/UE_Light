// Fill out your copyright notice in the Description page of Project Settings.


#include "LightOpening.h"
#include "Components\PointLightComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ALightOpening::ALightOpening()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 开关的静态网格体
	StaticMeshFire = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshFire"));
	//StaticMeshFire->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Main/Mesh/SM_CornerFrame.SM_CornerFrame"));	// 读取静态网格体资源
	if (CubeVisualAsset.Succeeded())
	{
		StaticMeshFire->SetStaticMesh(CubeVisualAsset.Object);
		StaticMeshFire->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMeshFire->SetCollisionEnabled(ECollisionEnabled::NoCollision);	// 关闭静态网格体的碰撞
	}

	// 碰撞包围盒
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(50, 100, 100));	// 包围盒范围
	BoxComponent->SetupAttachment(StaticMeshFire);
	BoxComponent->SetRelativeLocation(GetActorLocation()+FVector(0,100,0));	// 包围盒与静态网格体位于同一原点
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

