// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "ZombiePawn.generated.h"

UENUM(Blueprintable, BlueprintType)
enum class EZombieState : uint8
{
	ZS_Idle,
	ZS_Patrolling,
	ZS_MoveToAttackPos,
	ZS_Attack,
	ZS_Dead
};

class AGun;

UCLASS()
class GAMEDEVNOSATOV3DP_API AZombiePawn : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	EZombieState _currentState = EZombieState::ZS_Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAIPerceptionComponent* _perceptions;

	UPROPERTY()
	UAISenseConfig_Sight* _sightConfig;

	UPROPERTY(EditDefaultsOnly, Category=Gun)
	TSubclassOf<AGun> GunClass;
	
	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly, Category=Gun)
	float FireRate = 1.f;

	UPROPERTY(VisibleDefaultsOnly, Category=Gun)
	USkeletalMeshComponent* _gun = nullptr;
	
public:
	// Sets default values for this pawn's properties
	AZombiePawn();

	UFUNCTION(BlueprintCallable)
	EZombieState GetCurrentState();

	UFUNCTION(BlueprintCallable)
	void ChangeState(EZombieState NewState);

	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintNativeEvent)
	void OnShootMade();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void PerceptionUpdated(const TArray<AActor*>& Actors);
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void PostInitializeComponents() override;

	FTimerHandle _fireTimerHandle;
	bool _isReadyToFire = true;

	UFUNCTION()
	void SetReadyToShoot();

	void OnShootMade_Implementation();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
