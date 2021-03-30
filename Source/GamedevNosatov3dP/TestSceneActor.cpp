// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSceneActor.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
ATestSceneActor::ATestSceneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	auto MeshForActor = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));
	ActorMesh->SetStaticMesh(MeshForActor.Object);
	
	RootComponent = ActorMesh;

	RandomMovementComponent = CreateDefaultSubobject<URandomMovementComponent>(TEXT("Random Movement Component"));
	RandomMovementComponent->MovementSpeed = 10;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

// Called when the game starts or when spawned
void ATestSceneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestSceneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATestSceneActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	HealthComponent->TakeDamage(DamageAmount);
	return DamageAmount;
}

