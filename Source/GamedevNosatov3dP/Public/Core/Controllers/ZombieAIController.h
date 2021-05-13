// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Behavior")
	UBehaviorTree* _baseBehaviorTree;

public:
	virtual void BeginPlay() override;
};
