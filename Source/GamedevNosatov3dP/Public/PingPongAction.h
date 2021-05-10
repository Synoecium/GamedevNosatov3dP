// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GAMEDEVNOSATOV3DP_API FPingPongAction : public FPendingLatentAction
{
public:
	FPingPongAction(AActor* InActor, FVector Start, FVector Target, const FLatentActionInfo& LatentInfo);

	AActor* PingPongActor;
	FVector StartLocation;
	FVector TargetLocation;

	bool bComplete;

	float TimeElapsed;
	float TotalTime;

	FName ExecutionFunction;

	int32 OutputLink;

	FWeakObjectPtr CallbackTarget;

	void UpdateOperation(FLatentResponse& Response) override;
	
};
