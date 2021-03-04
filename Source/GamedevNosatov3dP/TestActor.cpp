// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Check test function from c++"));
    UFloatProperty* FloatProp = FindField<UFloatProperty>(this->GetClass(), TEXT("Testfloat"));
    if (FloatProp != nullptr)
    {
        float FloatValue = FloatProp->GetPropertyValue_InContainer(this);
        UE_LOG(LogTemp, Warning, TEXT("Testfloat value = %f"), FloatValue);
    }

	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("test"), ar, this, true);
	UE_LOG(LogTemp, Warning, TEXT("Set the new value..."));

    if (FloatProp != nullptr)
    {
        float FloatValue = FloatProp->GetPropertyValue_InContainer(this);
        UE_LOG(LogTemp, Warning, TEXT("Testfloat value = %f"), FloatValue);
    }

}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

