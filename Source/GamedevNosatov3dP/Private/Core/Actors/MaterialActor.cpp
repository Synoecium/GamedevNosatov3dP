// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/MaterialActor.h"

#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AMaterialActor::AMaterialActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

}

// Called when the game starts or when spawned
void AMaterialActor::BeginPlay()
{
	Super::BeginPlay();
	_DynamicMatInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
/*
	//Generate random RGB and Alpha values for our Vector Parameter
	FLinearColor RandomColor;
	RandomColor.R = FMath::RandRange(0,1);
	RandomColor.G = FMath::RandRange(0,1);
	RandomColor.B = FMath::RandRange(0,1);
	RandomColor.A = FMath::RandRange(0,1);

	//If we have a valid dynamic material instance, modify its parameters
	if (DynamicMatInstance)
	{
		DynamicMatInstance->SetVectorParameterValue(FName("Color_Param"), RandomColor);
		DynamicMatInstance->SetScalarParameterValue(FName("Met_Param"), FMath::RandRange(0,1));
	}
*/
	if (!ColorCurve)
	{
		UE_LOG(LogTemp, Error, TEXT("Set the curve vector for the color animation!"));
		return;
	}
	if (!MetallicCurve)
	{
		UE_LOG(LogTemp, Error, TEXT("Set the curve float for the metallic animation!"));
		return;
	}

	ColorCurve->GetTimeRange(_startTimeColor, _endTimeColor);
	MetallicCurve->GetTimeRange(_startTimeMet, _endTimeMet);
}

// Called every frame
void AMaterialActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_elapsedTime += DeltaTime;
	if (_elapsedTime > AnimationTime) _elapsedTime = FMath::Fmod(_elapsedTime, AnimationTime);
	
	auto color =  ColorCurve->GetVectorValue(_startTimeColor + (_elapsedTime / AnimationTime) * (_endTimeColor - _startTimeColor));
	auto met =  MetallicCurve->GetFloatValue(_startTimeMet + (_elapsedTime / AnimationTime) * (_endTimeMet - _startTimeMet));
	if (_DynamicMatInstance->IsValidLowLevel())
	{
		_DynamicMatInstance->SetVectorParameterValue(FName("Color_Param"), color);
		_DynamicMatInstance->SetScalarParameterValue(FName("Met_Param"), met);
	}
}

