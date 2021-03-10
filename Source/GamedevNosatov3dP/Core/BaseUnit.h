// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseUnit.generated.h"

UCLASS()
class GAMEDEVNOSATOV3DP_API ABaseUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseUnit();

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* BaseSceletalComp;

	void Init(float parHealth, float parArmor, float parDamage);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float Health;
	float Armor;
	float Damage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
