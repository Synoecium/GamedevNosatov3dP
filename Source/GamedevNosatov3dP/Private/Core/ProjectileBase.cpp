// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProjectileBase.h"

#include "DestructibleActor.h"
#include "DestructibleComponent.h"
#include "DrawDebugHelpers.h"
#include "Chaos/GeometryParticlesfwd.h"
#include "Components/StaticMeshComponent.h"
#include "Core/Controllers/BasePlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.f;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	
}



void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalInputs, const FHitResult& Hit) 
{
	
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		ADestructibleActor* Des = Cast<ADestructibleActor>(OtherActor);
		if (Des)
		{
			FVector ImpulseDir = Hit.Normal;
			//ImpulseDir = Hit.ImpactNormal;
			//ImpulseDir = FVector(0.5, 0, 0.5);
			ImpulseDir = -ImpulseDir;
			FVector Location = Des->GetActorLocation();
			Location = Hit.Location;
			//DrawDebugLine(GetWorld(), Location, Location+ImpulseDir*50,FColor::Red, false, 5);
			DrawDebugDirectionalArrow(GetWorld(), Location, Location+ImpulseDir*100, 30, FColor::Red, false, 10);
			Des->GetDestructibleComponent()->ApplyDamage(Damage, Location, ImpulseDir, ImpulseStrength);
			UE_LOG(LogTemp, Warning, TEXT("Destructible actor damaged! Normal inputs %f %f %f Location %f %f %f")
				, ImpulseDir.X, ImpulseDir.Y, ImpulseDir.Z, Location.X, Location.Y, Location.Z);

		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		}
		
		//UE_LOG(LogTemp, Warning, TEXT("Projectile hit and destroyed"));
		
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);

		if (OtherActor->ActorHasTag(FName("ComboCount")))
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s actor hit"), *OtherActor->GetName());
			_bUsefulAimHit = true;
		}

		
		Destroy();
	}
}

void AProjectileBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	auto playerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	if (playerController)
	{
		if (_bUsefulAimHit)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Player hit the aim!"));
			//playerController->OnPlayerHitAim.Broadcast();
			playerController->RegisterHitAim();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Player missed!"));
			playerController->OnPlayerMissAim.Broadcast();
		}
	};

}
