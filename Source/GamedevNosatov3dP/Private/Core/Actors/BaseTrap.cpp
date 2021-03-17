// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/BaseTrap.h"

#include "Core/Actors/BaseUnit.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetBoxExtent(FVector(50));

	SetRootComponent(Trigger);
	BaseMesh->SetupAttachment(GetRootComponent());

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrap::OnTriggerOverlapped);

}

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();
	
}



//BaseTrap.cpp
void ABaseTrap::OnTriggerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Trap %s activated!"), *GetName());
	bool IsDamageable = OtherActor->Implements<UDamageInterface>();
	IDamageInterface* Interface = Cast<IDamageInterface>(OtherActor);
	if (Interface)
	{
		FDamageParams params;
		params.DamageValue = Damage;
		params.DamageMaker = this;
		Interface->ApplyDamage(params);
	}
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

