// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"



#include "Components/WidgetComponent.h"
#include "Core/Controllers/BasePlayerController.h"
#include "Core/Interfaces/Saveable.h"
#include "GameFramework/Character.h"
#include "GamedevNosatov3dPCharacter.generated.h"

class AGun;

USTRUCT()
struct FS
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	int32 TestVar;	
};

UCLASS(config=Game)
class AGamedevNosatov3dPCharacter : public ACharacter, public ISaveable
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* ButtonComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ButtonClass;

public:
	AGamedevNosatov3dPCharacter();

	virtual void BeginPlay() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category="Test")
	FName TestMontageSectionName;

	UPROPERTY(EditDefaultsOnly, Category="Test")
	UAnimMontage* TestMontageRef;
	
	UFUNCTION(BlueprintPure)
    bool IsDead() const;

	void Shoot();

	float PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName) override;
	
	bool IsAnimationBlended() {return true;};
	bool IsArmed() {return true;};

protected:

	void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void LookUpRate(float AxisValue);
    void LookRight(float AxisValue);
    void LookRightRate(float AxisValue);
    virtual void Jump() override;
	void StartCrouch();
	void StopCrouch();
	virtual bool CanCrouch() const override;
	void AnimationTest();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// float WeaponRange = 5000.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
	
	UPROPERTY()
    AGun* Gun;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:

	virtual void Saved() override;
	virtual void Loaded() override;
	virtual void PreSaved() override {};
	virtual void PreLoaded() override {};

	UFUNCTION(BlueprintCallable)
	void Save(ABasePlayerController* Player);

	UFUNCTION(BlueprintCallable)
	void Load(ABasePlayerController* Player);

private:
	UPROPERTY(SaveGame)
	int32 TestVar = 0;

	UPROPERTY(SaveGame)
	FS TestStruct;
};

