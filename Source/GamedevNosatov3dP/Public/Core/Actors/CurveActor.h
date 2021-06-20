// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurveActor.generated.h"

class UBoxComponent;
class UTimelineComponent;

UCLASS()
class GAMEDEVNOSATOV3DP_API ACurveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACurveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorCurve;

	UPROPERTY(EditAnywhere)
	float RotateAngle = 90.f;
	
	UFUNCTION()
	void ControlDoor();

	UFUNCTION(BlueprintCallable)
	void ToogleDoor();

	UFUNCTION()
	void SetState();

	bool Open;
	bool ReadyState;
	float RotateValue;
	float CurveFloatValue;
	float TimelineValue;
	UTimelineComponent* MyTimeline;

};
