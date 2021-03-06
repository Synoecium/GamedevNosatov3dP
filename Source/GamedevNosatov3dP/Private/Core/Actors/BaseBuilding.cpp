// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/BaseBuilding.h"

#include "Core/Configs/BaseUnitConfig.h"

// Sets default values
ABaseBuilding::ABaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	BaseSpawnPont = CreateDefaultSubobject<USceneComponent>(TEXT("BaseSpawnPont"));
	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("SplinePath"));
	RootComponent = RootComp;

	BaseMesh->SetupAttachment(RootComponent);
	BaseSpawnPont->SetupAttachment(RootComponent);
	SplinePath->SetupAttachment(RootComponent);
	
}

void ABaseBuilding::SpawnUnit()
{
	ABaseUnit* SpawnedUnit = ABaseBuilding::Create_Unit(CurrentUnitConfig);
	SpawnedUnit->SetActorLocation(BaseSpawnPont->GetComponentLocation());
	SpawnedUnit->SetPath(PathPoints);
	OnSpawnUnitChanged.Broadcast(SpawnedUnit);

	ABaseUnit* SpawnedUnit2 = ABaseBuilding::Create_Unit(CurrentUnitConfig);
	SpawnedUnit2->SetActorLocation(BaseSpawnPont->GetComponentLocation());
	OnSpawnUnitChanged.Broadcast(SpawnedUnit2);
}

ABaseUnit* ABaseBuilding::Create_Unit(UBaseUnitConfig* config)
{
	UWorld* CurrentWorld = config->GetWorld();
	ABaseUnit* Unit = Cast<ABaseUnit>(CurrentWorld->SpawnActor(config->UnitClass));
	Unit->Init(config->Health, config->Armour, config->Damage, config->Speed);
	return Unit;
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	CurrentUnitConfig = NewObject<UBaseUnitConfig>(this, UnitConfiguration);
	Super::BeginPlay();

	PathPoints.Empty();
	const int32 PointsNum = SplinePath->GetNumberOfSplinePoints();
	for (int32 i=0; i<PointsNum; i++)
	{
		PathPoints.Add(SplinePath->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
	}
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

