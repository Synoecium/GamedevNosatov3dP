// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BTS_UpdateTargetActorPosition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_UpdateTargetActorPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* aiController = OwnerComp.GetAIOwner();
	UBlackboardComponent* blackBoard = aiController->GetBlackboardComponent();
	AActor* targetActor = Cast<AActor>(blackBoard->GetValueAsObject("TargetActor"));
	if (targetActor)
	{
		FVector newPosition = targetActor->GetActorLocation();
		blackBoard->SetValueAsVector("DestinationPoint", newPosition);	
	}


}
