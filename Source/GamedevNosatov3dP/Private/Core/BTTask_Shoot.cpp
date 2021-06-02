// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BTTask_Shoot.h"

#include "AIController.h"
#include "Core/Actors/ZombiePawn.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* aiController = OwnerComp.GetAIOwner();
	AZombiePawn* aiPawn = Cast<AZombiePawn>(aiController->GetPawn());
	if (aiPawn)
	{
		aiPawn->Shoot();
	}
	return EBTNodeResult::Type::Succeeded;
}
