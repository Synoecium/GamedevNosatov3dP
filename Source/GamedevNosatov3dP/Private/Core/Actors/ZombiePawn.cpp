// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/ZombiePawn.h"
#include "Core/Gun.h"

#include "AIController.h"
#include "GamedevNosatov3dPCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
AZombiePawn::AZombiePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_perceptions = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perceptions"));
	_sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	_perceptions->ConfigureSense(*_sightConfig);
	_perceptions->SetDominantSense(_sightConfig->GetSenseImplementation());

	_sightConfig->SightRadius = 2000;
	_sightConfig->LoseSightRadius = 2300;
	_sightConfig->PeripheralVisionAngleDegrees = 45;
	_sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	_sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	_sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//UWorld* CurrentWorld = GetWorld();
	//if (CurrentWorld==nullptr) return;
	/*if (!GunClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set the Gun Class for ZombiePawn!"));
		return;
	}
	Gun = CreateDefaultSubobject<GunClass>(TEXT("GUN"));
	//Gun = CurrentWorld->SpawnActor<AGun>(GunClass);
	
	auto MainMesh = GetMesh();
	MainMesh->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	if (MainMesh->DoesSocketExist(TEXT("WeaponSocket")))
	{
		Gun->AttachToComponent(MainMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Mesh for ZombiePawn doesn't have \"WeaponSocket\" socket!"));
	}	
	Gun->SetOwner(this);
	*/

	_gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skel_GUN"));
	if (_gun)
	{
		/*UE_LOG(LogTemp, Warning,TEXT("Gun created"));
		_gun->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
		auto defOb = Cast<AGun>(GunClass->CreateDe);
		if (defOb)
		{
			UE_LOG(LogTemp, Warning,TEXT("Default object from Gun got"));
			auto comps = defOb->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
			if (comps.Num()>0)
			{
				UE_LOG(LogTemp, Warning,TEXT("Found skeletal mesh components"));
				auto skelMeshComp = Cast<USkeletalMeshComponent>(comps[0]);
				if (skelMeshComp)
				{
					UE_LOG(LogTemp, Warning,TEXT("Casted to skeletal mesh component"));
					_gun->SetSkeletalMesh(skelMeshComp->SkeletalMesh);
				}
			
			}
		}*/
	}

}

EZombieState AZombiePawn::GetCurrentState()
{
	return _currentState;
}

void AZombiePawn::ChangeState(EZombieState NewState)
{
	_currentState = NewState;
	switch (_currentState)
	{
		case EZombieState::ZS_Patrolling:
			{
				UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
				if (CharacterMovementComponent)
				{
					CharacterMovementComponent->MaxWalkSpeed = 100;
				}
			}
		break;

		case EZombieState::ZS_MoveToAttackPos:
			{
				UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
				if (CharacterMovementComponent)
				{
					CharacterMovementComponent->MaxWalkSpeed = 350;
				}
			}
		break;
	}
}

void AZombiePawn::Shoot()
{
	if (!_isReadyToFire) return;

	_isReadyToFire = false;
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld==nullptr) return;
	CurrentWorld->GetTimerManager().ClearTimer(_fireTimerHandle);
	CurrentWorld->GetTimerManager().SetTimer(_fireTimerHandle, this, &AZombiePawn::SetReadyToShoot, FireRate, false);
	UE_LOG(LogTemp, Warning, TEXT("Fire made"));

	if (Gun == nullptr) return;
	
	Gun->PullTrigger();

}

void AZombiePawn::SetReadyToShoot()
{
	_isReadyToFire = true;
}

void AZombiePawn::OnShootMade_Implementation()
{
}

// Called when the game starts or when spawned
void AZombiePawn::BeginPlay()
{
	Super::BeginPlay();
/*
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld==nullptr) return;
	if (!GunClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set the Gun Class for ZombiePawn!"));
		return;
	}
	Gun = CurrentWorld->SpawnActor<AGun>(GunClass);
	
	auto MainMesh = GetMesh();
	MainMesh->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	if (MainMesh->DoesSocketExist(TEXT("WeaponSocket")))
	{
		Gun->AttachToComponent(MainMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Mesh for ZombiePawn doesn't have \"WeaponSocket\" socket!"));
	}	
	Gun->SetOwner(this);
	*/
	
}

void AZombiePawn::PerceptionUpdated(const TArray<AActor*>& Actors)
{
	int32 actorsNum = Actors.Num();
	for (int32 i = 0; i<actorsNum; i++)
	{
		AGamedevNosatov3dPCharacter* playerCharacter = Cast<AGamedevNosatov3dPCharacter>(Actors[i]);
		if (playerCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT(" %s seen %s"), *GetName(), *Actors[i]->GetName());
			AAIController* controller = Cast<AAIController>(GetController());
			if (controller)
			{
				UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
				if (blackboard->GetValueAsObject("TargetActor") != playerCharacter)
				{
					blackboard->SetValueAsObject("TargetActor", playerCharacter);
					
				}
			}
		}
	}
	
}

void AZombiePawn::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AGamedevNosatov3dPCharacter* playerCharacter = Cast<AGamedevNosatov3dPCharacter>(Actor);
	AAIController* controller = Cast<AAIController>(GetController());
	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();
	if (playerCharacter)
	{
		if (Stimulus.IsActive())
		{
			UE_LOG(LogTemp, Warning, TEXT(" %s seen %s"), *GetName(), *Actor->GetName());
			blackboard->SetValueAsObject("TargetActor", playerCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" %s loose %s"), *GetName(), *Actor->GetName());
			blackboard->SetValueAsObject("TargetActor", nullptr);
		}
		
	}
}

void AZombiePawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//_perceptions->OnPerceptionUpdated.AddDynamic(this, &AZombiePawn::PerceptionUpdated);
	_perceptions->OnTargetPerceptionUpdated.AddDynamic(this, &AZombiePawn::TargetPerceptionUpdated);


}

// Called every frame
void AZombiePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombiePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

