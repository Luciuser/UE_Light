// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightCharacter.h"
#include "LightGameMode.h"
#include "Components\SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ALightCharacter

ALightCharacter::ALightCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// 聚光灯
	SpotBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpotLightBoom"));
	SpotBoom->SetupAttachment(RootComponent);
	SpotBoom->TargetArmLength = 100.0f; // The camera follows at this distance behind the character	
	SpotBoom->bUsePawnControlRotation = false;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(SpotBoom, USpringArmComponent::SocketName);
	SpotLight->SetVisibility(true);
	SpotLight->SetLightColor(FLinearColor(1, 1, 1, 1));
	SpotLight->SetIntensity(3000);
	SpotLight->SetOuterConeAngle(40);
	
	SpotLightNextOpenState = false;
	SpotIntensityMin = 3000;
	SpotIntensityMax = 20000;
	SpotIntensityChangeSpeed = 2000;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALightCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALightCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALightCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALightCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALightCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALightCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALightCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ALightCharacter::OnResetVR);

	// 互动
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALightCharacter::OnInteract);

	// 退出QuitGame
	PlayerInputComponent->BindAction("QuitGame", IE_Pressed, this, &ALightCharacter::QuitGame);

	// 操控聚光灯
	PlayerInputComponent->BindAction("ChangeSpotLightVisibility", IE_Pressed, this, &ALightCharacter::ChangeSpotLightVisibility);
	PlayerInputComponent->BindAction("AddSpotIntensity", IE_Pressed, this, &ALightCharacter::AddSpotIntensity);
	PlayerInputComponent->BindAction("SubtractSpotIntensity", IE_Pressed, this, &ALightCharacter::SubtractSpotIntensity);
	PlayerInputComponent->BindAction("ChangeSpotLightTypeTo1", IE_Pressed, this, &ALightCharacter::ChangeSpotLightTypeTo1);
	PlayerInputComponent->BindAction("ChangeSpotLightTypeTo2", IE_Pressed, this, &ALightCharacter::ChangeSpotLightTypeTo2);
	PlayerInputComponent->BindAction("ChangeSpotLightTypeTo3", IE_Pressed, this, &ALightCharacter::ChangeSpotLightTypeTo3);
}

void ALightCharacter::ChangeSpotLightVisibility()
{
	SpotLight->SetVisibility(SpotLightNextOpenState);
	SpotLightNextOpenState = !SpotLightNextOpenState;
}

void ALightCharacter::AddSpotIntensity()
{
	ChangeSpotLightIntensity(1);
}

void ALightCharacter::SubtractSpotIntensity()
{
	ChangeSpotLightIntensity(-1);
}

void ALightCharacter::ChangeSpotLightTypeTo1()
{
	ChangeSpotLightType(1);
}

void ALightCharacter::ChangeSpotLightTypeTo2()
{
	ChangeSpotLightType(2);

}

void ALightCharacter::ChangeSpotLightTypeTo3()
{
	ChangeSpotLightType(3);
}

void ALightCharacter::ChangeSpotLightType(int lightType)
{
	SpotLight->SetInnerConeAngle((lightType - 1) * 20);
	SpotLight->SetOuterConeAngle(lightType * 40);
}

void ALightCharacter::ChangeSpotLightIntensity(int direction)
{
	float NextIntensity = SpotLight->Intensity + direction * SpotIntensityChangeSpeed;
	if (SpotIntensityMin <= NextIntensity && NextIntensity <= SpotIntensityMax) {
		SpotLight->SetIntensity(NextIntensity);
	}
}

void ALightCharacter::OnInteract()
{
	// 目前仅有开关，因此同开关互动
	UWorld* world = GetWorld();
	ALightGameMode *LightGameMode = Cast<ALightGameMode>(UGameplayStatics::GetGameMode(world));	// 获取GameMode类
	if (LightGameMode->CurrentLightOpening != nullptr) {
		LightGameMode->CurrentLightOpening->LightChange();
	}
}

void ALightCharacter::QuitGame()
{
	APlayerController *PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController != nullptr) {
		//EatCoinPlayerController->Save();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Quit."));
		UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
	}
}

void ALightCharacter::OnResetVR()
{
	// If Light is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Light.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ALightCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ALightCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ALightCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALightCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALightCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALightCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
