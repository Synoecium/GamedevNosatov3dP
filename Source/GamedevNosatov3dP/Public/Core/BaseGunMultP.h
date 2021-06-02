// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Gun.h"
#include "BaseGunMultP.generated.h"

UCLASS()
class GAMEDEVNOSATOV3DP_API ABaseGunMultP : public AGun
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGunMultP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void OnFire();
};
