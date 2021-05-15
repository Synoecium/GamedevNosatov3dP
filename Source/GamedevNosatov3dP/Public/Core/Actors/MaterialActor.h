// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Curves/CurveVector.h"
#include "GameFramework/Actor.h"
#include "MaterialActor.generated.h"

UCLASS()
class GAMEDEVNOSATOV3DP_API AMaterialActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaterialActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector* ColorCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* MetallicCurve;

	UPROPERTY(EditAnywhere)
	float AnimationTime = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float _startTimeColor, _endTimeColor;
	float _startTimeMet, _endTimeMet;

	float _elapsedTime = 0.f;

	UMaterialInstanceDynamic* _DynamicMatInstance;

};
