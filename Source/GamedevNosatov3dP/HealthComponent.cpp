// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	CurrentHealth-=DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Current health is: %f"), CurrentHealth);
	if (CurrentHealth<=0.f)
	{
		AActor* Parent = GetOwner();
		if (Parent)
		{
			
			Parent->Destroy();
			Parent->MarkPendingKill();
		}
	}
}

