// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/InterpToMovementComponent.h"
#include "Core/Interfaces/DamageInterface.h"
#include "GameFramework/Actor.h"
#include "BaseUnit.generated.h"

UCLASS()
class GAMEDEVNOSATOV3DP_API ABaseUnit : public APawn, public IDamageInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseUnit();

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* BaseSceletalComp;
	
	UPROPERTY(VisibleAnywhere)
	UInterpToMovementComponent* MoveComponent;

	UPROPERTY(VisibleAnywhere)
	float Speed;

	void Init(float parHealth, float parArmor, float parDamage, float parSpeed);

	void SetPath(TArray<FVector> Points);

public:
	bool operator==(int32 Other) {return true;};
	//virtual bool operator==(int32 Other) = delete;
	//bool operator==(int32 Other) = delete;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float Health;
	float Armor;
	float Damage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//BaseUnit.h
	virtual void ApplyDamage(FDamageParams DamageParams) override;
};
