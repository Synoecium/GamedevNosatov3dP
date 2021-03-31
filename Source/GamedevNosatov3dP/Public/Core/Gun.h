// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AProjectileBase;

UCLASS()
class GAMEDEVNOSATOV3DP_API AGun : public AActor
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;
	
	private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;



	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	bool GunTrace(FHitResult& Hit,FVector& ShotDirection);

	AController* GetOwnerController() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile type", meta = (AllowPrivateAccess = true))
	TSubclassOf<AProjectileBase> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    USceneComponent* ProjectileSpawnPoint;
};
