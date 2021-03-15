// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/BaseUnit.h"

// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSceletalComp = CreateDefaultSubobject<USkeletalMeshComponent>("BaseSceletalComp");
	RootComponent = BaseSceletalComp;

}

void ABaseUnit::Init(float parHealth, float parArmor, float parDamage)
{
	Health = parHealth;
	Armor = parArmor;
	Damage = parDamage;
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

