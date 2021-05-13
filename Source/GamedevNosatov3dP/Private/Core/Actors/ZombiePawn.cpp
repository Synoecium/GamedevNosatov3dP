// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/ZombiePawn.h"

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

// Called when the game starts or when spawned
void AZombiePawn::BeginPlay()
{
	Super::BeginPlay();
	
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

void AZombiePawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_perceptions->OnPerceptionUpdated.AddDynamic(this, &AZombiePawn::PerceptionUpdated);


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

