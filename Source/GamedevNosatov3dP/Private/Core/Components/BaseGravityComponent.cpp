// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/BaseGravityComponent.h"
#include "Core/Actors/BaseUnit.h"

// Sets default values for this component's properties
USomeGravityComponent::USomeGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RootActor = nullptr;
	bEnableGravity = false;
	DeltaGravityMultiplier = 0.098f;
	OnActivateGravity.BindUObject(this,&USomeGravityComponent::OnGravityActivate);
}


// Called when the game starts
void USomeGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	RootActor = GetOwner();	
	
}


void USomeGravityComponent::OnGravityActivate(ABaseUnit* UnitThatActivateGravity)
{
	bEnableGravity = true;
}

// Called every frame
void USomeGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEnableGravity)
	{
		FVector CurrentLocation = RootActor->GetActorLocation();	
		FVector DeltaVector(0,0, DeltaGravityMultiplier);
		CurrentLocation+=DeltaVector;
		RootActor->SetActorLocation(CurrentLocation);
		
	}
}

