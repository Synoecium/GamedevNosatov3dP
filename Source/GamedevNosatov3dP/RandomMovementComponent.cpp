// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMovementComponent.h"

// Sets default values for this component's properties
URandomMovementComponent::URandomMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MovementSpeed = 5;
}


// Called when the game starts
void URandomMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URandomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentRandomTime-=DeltaTime;

	if (CurrentRandomTime<0.f)
	{
		CurrentRandomTime = FMath::FRandRange(1, 5);
		CurrentDirection = FVector(
		FMath::FRandRange(-1, 1),
		FMath::FRandRange(-1, 1),
		FMath::FRandRange(-1, 1));
	}

	

	AActor* Parent = GetOwner();
	if (Parent)
	{
		Parent->SetActorLocation(
        Parent->GetActorLocation() + CurrentDirection * DeltaTime * MovementSpeed);
	}


}

