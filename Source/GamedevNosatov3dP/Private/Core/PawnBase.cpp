// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Core/ProjectileBase.h"
#include "GamedevNosatov3dP/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	
}

void APawnBase::RotateTurret(FVector LookAtTarget) 
{
	FVector StartLocation = TurretMesh->GetComponentLocation(); 
	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, StartLocation.Z);

	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire() 
{
	// UE_LOG(LogTemp, Warning, TEXT("Fire condition success"));
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

//PZ #5 start
void APawnBase::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Pawn takes damage"));
	HealthComponent->TakeDamage(15.f);
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
	TurretMesh->OnComponentHit.AddDynamic(this, &APawnBase::OnComponentHit);
}

void APawnBase::Destroyed()
{
	Super::Destroyed();
	UE_LOG(LogTemp, Warning, TEXT("Pawn destroyed!"));
	
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());	
	
	if (OnPawnKilled.IsBound())
	{
		OnPawnKilled.Broadcast();
	}
}
//PZ #5 finish



