// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BTTask_FindRandomPosition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	APawn* aiPawn = aiController->GetPawn();
	FVector newPosition = aiPawn->GetActorLocation() + aiPawn->GetActorForwardVector() * FMath::RandRange(-500, 500)
		+aiPawn->GetActorRightVector() * FMath::RandRange(-500, 500);

	UBlackboardComponent* blackBoard = aiController->GetBlackboardComponent();
	blackBoard->SetValueAsVector("DestinationPoint", newPosition);
	return EBTNodeResult::Type::Succeeded;
}
