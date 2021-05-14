// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/EnemyPatrol.h"

// Sets default values
AEnemyPatrol::AEnemyPatrol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComp = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("MovComponent"));
	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	//CurveComp = CreateDefaultSubobject<UCurveVector>(TEXT("CurveComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	RootComponent = MeshComp;

	SplineComp->SetupAttachment(RootComponent);

	MovementComp->BehaviourType = EInterpToBehaviourType::PingPong;
}

// Called when the game starts or when spawned
void AEnemyPatrol::BeginPlay()
{
	Super::BeginPlay();
/*
	FInterpCurveVector V = SplineComp->GetSplinePointsPosition();

	for (int i=0; i<V.Points.Num(); i++)
	{
		MovementComp->AddControlPointPosition(V.Points[i].OutVal, true);
	}
*/

	if (!CurveComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Set the curve vector for the Enemy patrol object!"));
		return;
	}
	
	float timeMin = 0.f, timeMax = 0.f;
	CurveComp->GetTimeRange(timeMin, timeMax);
	float timeDelta = (timeMax-timeMin)/10.f;
	for (float timeCurrent = timeMin; timeCurrent<=timeMax; timeCurrent+=timeDelta)
	{		
		auto point = CurveComp->GetVectorValue(timeCurrent);
		MovementComp->AddControlPointPosition(point*3.f, true);
	}
	

	MovementComp->FinaliseControlPoints();
}

// Called every frame
void AEnemyPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

