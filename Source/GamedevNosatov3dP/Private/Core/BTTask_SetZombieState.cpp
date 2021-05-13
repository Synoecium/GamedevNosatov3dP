// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BTTask_SetZombieState.h"

#include "AIController.h"

EBTNodeResult::Type UBTTask_SetZombieState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	AZombiePawn* aiPawn = Cast<AZombiePawn>(aiController->GetPawn());
	if (aiPawn)
	{
		aiPawn->ChangeState(_newState);
	}
	return EBTNodeResult::Type::Succeeded;
}
