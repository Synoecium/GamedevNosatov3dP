// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Controllers/ZombieAIController.h"

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	if (_baseBehaviorTree)
	{
		RunBehaviorTree(_baseBehaviorTree);
	}
	
}
