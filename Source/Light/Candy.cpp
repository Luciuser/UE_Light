// Fill out your copyright notice in the Description page of Project Settings.


#include "Candy.h"
#include "Components\PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "LightCharacter.h"
#include "LightGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACandy::ACandy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshRoot"));
	StaticMeshRoot->SetupAttachment(RootComponent);

	// ����ľ�̬������
	StaticMeshFire = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshFire"));
	//StaticMeshFire->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Main/Mesh/CandleSticks/Fire.Fire"));	// ��ȡ��̬��������Դ
	if (CubeVisualAsset.Succeeded())
	{
		StaticMeshFire->SetStaticMesh(CubeVisualAsset.Object);
		StaticMeshFire->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMeshFire->SetCollisionEnabled(ECollisionEnabled::NoCollision);	// �رվ�̬���������ײ
	}

	// ���Դ
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	//PointLight->SetupAttachment(RootComponent);
	PointLight->SetVisibility(true);	
	PointLight->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	PointLight->SetLightColor(FLinearColor(0.37, 0, 0.01, 1));
	LightOpenNext = false;

	// ��ײ��Χ��
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(500, 500, 1000));	// ��Χ�з�Χ
	BoxComponent->SetupAttachment(StaticMeshFire);
	BoxComponent->SetRelativeLocation(GetActorLocation());	// ��Χ���뾲̬������λ��ͬһԭ��
	BoxComponent->SetCollisionProfileName("Trigger");


	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACandy::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACandy::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACandy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACandy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ��Χ����ײ����
void ACandy::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Test"));
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ALightCharacter *PlayerCharacter = Cast<ALightCharacter>(OtherActor); // ȷ����ײ�Ķ���
		if (PlayerCharacter != nullptr) {
			UWorld* world = GetWorld();
			ALightGameMode *LightGameMode = Cast<ALightGameMode>(UGameplayStatics::GetGameMode(world));	// ��ȡGameMode��
			//LightGameMode->CurrentCandy = this;	// ��GameMode�������ֵ

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("This candy saved."));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("The actor overlaped is not player"));
		}
	}
}

void ACandy::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Test"));
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ALightCharacter *PlayerCharacter = Cast<ALightCharacter>(OtherActor); // ȷ����ײ�Ķ���
		if (PlayerCharacter != nullptr) {
			UWorld* world = GetWorld();
			ALightGameMode *LightGameMode = Cast<ALightGameMode>(UGameplayStatics::GetGameMode(world));	// ��ȡGameMode��
			//LightGameMode->CurrentCandy = nullptr;	// ��GameMode�������ֵ

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("This candy deleted."));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("The actor overlaped is not player"));
		}
	}
}

void ACandy::LightChange()
{
	// ����Ļ��ͻ����Ƿ����
	PointLight->SetVisibility(LightOpenNext);
	StaticMeshFire->SetVisibility(LightOpenNext);

	LightOpenNext = !LightOpenNext;
}
