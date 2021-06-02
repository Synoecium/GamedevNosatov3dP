// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BTTask_MyWait.h"


UBTTask_MyWait::UBTTask_MyWait(const FObjectInitializer& ObjectInitializer) : Super()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MyWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	_currTime = 0;

	return EBTNodeResult::InProgress;
}

void UBTTask_MyWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	_currTime += DeltaSeconds;
	if (_currTime >= WaitTime)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);	
	}
}
