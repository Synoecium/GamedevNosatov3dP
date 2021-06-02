// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BaseGunMultP.h"

#include "Core/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseGunMultP::ABaseGunMultP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGunMultP::BeginPlay()
{
	Super::BeginPlay();
	
}
/*
void ABaseGunMultP::OnFire_Implementation()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if (ProjectileSpawnPoint)
			{
				FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
				FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
				FActorSpawnParameters ActorSpawnParameters;
				ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParameters);
				TempProjectile->SetOwner(this);
		
			}		
		}
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

bool ABaseGunMultP::OnFire_Validate()
{
	return true;
}
*/
void ABaseGunMultP::PullTrigger()
{
	OnFire();
}

// Called every frame
void ABaseGunMultP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


