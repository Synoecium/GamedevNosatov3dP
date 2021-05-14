// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/InterpToMovementComponent.h"
#include "Components/SplineComponent.h"
#include "Curves/CurveVector.h"
#include "GameFramework/Actor.h"
#include "EnemyPatrol.generated.h"

UCLASS()
class GAMEDEVNOSATOV3DP_API AEnemyPatrol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyPatrol();

	UPROPERTY(VisibleAnywhere)
	UInterpToMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector* CurveComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
