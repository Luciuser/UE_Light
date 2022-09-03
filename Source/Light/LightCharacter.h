// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LightCharacter.generated.h"

UCLASS(config=Game)
class ALightCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ALightCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// �۹�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* SpotBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpotLightComponent* SpotLight;	// �۹�������ֱ�Ӷ�ȡ��ͼ�еľ۹��
	
	// ��¼�۹�Ƶ�ǰ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float SpotIntensityMin; // �۹����С����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float SpotIntensityMax; // �۹���������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float SpotIntensityChangeSpeed; // �۹�����ȵı仯ֵ 
	bool SpotLightNextOpenState; // �۹����һ���Ƿ�򿪵�״̬

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// �������е����廥��
	void OnInteract();

	// �˳���Ϸ
	void QuitGame();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

private:
	// ͬ�Դ��۹�ƵĻ���
	void ChangeSpotLightVisibility();
	void AddSpotIntensity();
	void SubtractSpotIntensity();
	void ChangeSpotLightTypeTo1();
	void ChangeSpotLightTypeTo2();
	void ChangeSpotLightTypeTo3();

	void ChangeSpotLightType(int lightType);
	void ChangeSpotLightIntensity(int direction);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

