// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/BaseUnit.h"

#include "Misc/TextFilterExpressionEvaluator.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSceletalComp = CreateDefaultSubobject<USkeletalMeshComponent>("BaseSceletalComp");
	RootComponent = BaseSceletalComp;

	MoveComponent = CreateDefaultSubobject<UInterpToMovementComponent>("Movement Component");

}

void ABaseUnit::Init(float parHealth, float parArmor, float parDamage, float parSpeed)
{
	Health = parHealth;
	Armor = parArmor;
	Damage = parDamage;
	Speed = parSpeed;
}

void ABaseUnit::SetPath(TArray<FVector> Points)
{
	MoveComponent->ResetControlPoints();
	float totalDistance  = 0;
	int32 pointsNum = Points.Num();
	for (int32 i = 0; i < pointsNum; ++i)
	{
		MoveComponent->AddControlPointPosition(Points[i], false);

		if (i<pointsNum-2)
		{
			totalDistance+=FVector::Distance(Points[i], Points[i+1]);
		}
	}

	float currDuration = totalDistance/Speed;
	MoveComponent->Duration = currDuration;

	UE_LOG(LogTemp, Warning, TEXT("Set path for %s. Distance: %f, Speed: %f, Duration: %f"), *GetName(), totalDistance, Speed, currDuration);
	/*for (FVector point : Points)
	{
		MoveComponent->AddControlPointPosition(point, false);
	}*/
	MoveComponent->FinaliseControlPoints();
	MoveComponent->RestartMovement();
}


// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseUnit::ApplyDamage(FDamageParams DamageParams)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s take damage %f from %s"), *GetName(), DamageParams.DamageValue, *DamageParams.DamageMaker->GetName());
}


