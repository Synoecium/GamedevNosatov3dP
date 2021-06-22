// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"



#include "Components/WidgetComponent.h"
#include "Core/MatineeSampleDistortion.h"
#include "Core/Controllers/BasePlayerController.h"
#include "Core/Interfaces/Saveable.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"

#include "GamedevNosatov3dPCharacter.generated.h"

class AGun;
class UTimelineComponent;
class UMatineeSampleDistortion;
class UFallShake;

USTRUCT()
struct FS
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	int32 TestVar;	
};

UENUM()
enum class EKnockbackState : uint8
{
	READY,
	KNOCKBACK,
	REVERSE
};

UCLASS(config=Game)
class AGamedevNosatov3dPCharacter : public ACharacter, public ISaveable, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	
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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category="Montage")
	FName TestMontageSectionName;

	UPROPERTY(EditDefaultsOnly, Category="Montage")
	UAnimMontage* TestMontageRef;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// float WeaponRange = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category="Gun")
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditAnywhere, Category="Common")
	float RotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly, Category="Common")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="Gun")
	float MaxKnockbackAngle = 40;

	UPROPERTY(EditAnywhere, Category="Gun")
	UCurveFloat* KnockbackCurve;

	UPROPERTY(BlueprintReadOnly, Category="Gun")
	float KnockbackAngleValue = 0;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UMatineeSampleDistortion> SampleDistortionClass;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TSubclassOf<UFallShake> FallShakeClass;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float HeightShakeTrigger;

public:
	
	UFUNCTION(BlueprintCallable)
	void Save(ABasePlayerController* Player);

	UFUNCTION(BlueprintCallable)
	void Load(ABasePlayerController* Player);

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable)
	void PlayKnockback();

public:
	AGamedevNosatov3dPCharacter();

	virtual void BeginPlay() override;
	float PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName) override;
	virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor) const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Landed(const FHitResult& Hit) override;

protected:

	void Shoot();
	


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

protected:
	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnGun();

	UFUNCTION()
	void ControlKnockback();

	UFUNCTION()
	void FinishKnockback();	


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Saved() override;
	virtual void Loaded() override;
	virtual void PreSaved() override {};
	virtual void PreLoaded() override {};

	bool IsAnimationBlended() {return true;};
	bool IsArmed() {return true;};

private:

	UPROPERTY(Replicated)
	AGun* Gun;
	
	UPROPERTY(SaveGame)
	int32 TestVar = 0;

	UPROPERTY(SaveGame)
	FS TestStruct;

	float CurrentHealth = 100.f;

	UTimelineComponent* KnockbackTimeline = nullptr;
	//float KnockbcakTimelinePos = 0;
	EKnockbackState KnockbcakState = EKnockbackState::READY;
};



