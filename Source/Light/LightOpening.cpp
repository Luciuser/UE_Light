// Fill out your copyright notice in the Description page of Project Settings.


#include "LightOpening.h"
#include "LightCharacter.h"
#include "LightGameMode.h"
#include "Components\SpotLightComponent.h"
#include "Components\PointLightComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
//#include "Public/EngineUtils.h"

// Sets default values
ALightOpening::ALightOpening()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���صľ�̬������
	StaticMeshLightOpening = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshLightOpening"));
	//StaticMeshFire->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Main/Mesh/SM_CornerFrame.SM_CornerFrame"));	// ��ȡ��̬��������Դ
	if (CubeVisualAsset.Succeeded())
	{
		StaticMeshLightOpening->SetStaticMesh(CubeVisualAsset.Object);
		StaticMeshLightOpening->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMeshLightOpening->SetCollisionEnabled(ECollisionEnabled::NoCollision);	// �رվ�̬���������ײ
	}

	// ��ײ��Χ��
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(50, 100, 100));	// ��Χ�з�Χ
	BoxComponent->SetupAttachment(StaticMeshLightOpening);
	BoxComponent->SetRelativeLocation(GetActorLocation()+FVector(0,100,0));	// ��Χ���뾲̬������λ��ͬһԭ��
	BoxComponent->SetCollisionProfileName("Trigger");

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightOpening::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALightOpening::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ALightOpening::BeginPlay()
{
	Super::BeginPlay();

	PlatLightNextState = false;
	OpenDoor = true;
	
	for (TActorIterator<APlatLight> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		ObjectArray.AddUnique(*Iterator);
	}
	for (TActorIterator<ADoor> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		ObjectDoor = (*Iterator);
		break;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x = %d"), ObjectArray.Num()));
}

// Called every frame
void ALightOpening::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightOpening::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ALightCharacter *PlayerCharacter = Cast<ALightCharacter>(OtherActor); // ȷ����ײ�Ķ���
		if (PlayerCharacter != nullptr) {
			UWorld* world = GetWorld();
			ALightGameMode *LightGameMode = Cast<ALightGameMode>(UGameplayStatics::GetGameMode(world));	// ��ȡGameMode��
			LightGameMode->CurrentLightOpening = this;	// ��GameMode�������ֵ

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("This light opening saved."));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("The actor overlaped is not player"));
		}
	}
}

void ALightOpening::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ALightCharacter *PlayerCharacter = Cast<ALightCharacter>(OtherActor); // ȷ����ײ�Ķ���
		if (PlayerCharacter != nullptr) {
			UWorld* world = GetWorld();
			ALightGameMode *LightGameMode = Cast<ALightGameMode>(UGameplayStatics::GetGameMode(world));	// ��ȡGameMode��
			LightGameMode->CurrentLightOpening = nullptr;	// ��GameMode�������ֵ

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("This light opening deleted."));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("The actor overlaped is not player"));
		}
	}
}

void ALightOpening::LightChange()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interact"));

	for (auto &Light : ObjectArray) {
		Light->SpotLight->SetVisibility(PlatLightNextState);
	}

	PlatLightNextState = !PlatLightNextState;
	if (OpenDoor) {
		OpenDoor = false;
		ObjectDoor->DoorOpen();
	}
}

