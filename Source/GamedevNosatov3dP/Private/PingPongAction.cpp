// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongAction.h"

FPingPongAction::FPingPongAction(AActor* InActor, FVector Start, FVector Target, const FLatentActionInfo& LatentInfo) :
	PingPongActor(InActor),
	StartLocation(Start),
	TargetLocation(Target),
	bComplete(false),
	TimeElapsed(0.f),
	TotalTime(1.f),
	ExecutionFunction(LatentInfo.ExecutionFunction),
	OutputLink(LatentInfo.Linkage),
	CallbackTarget(LatentInfo.CallbackTarget)
	
{
	
}

void FPingPongAction::UpdateOperation(FLatentResponse& Response)
{
	TimeElapsed += Response.ElapsedTime();
	float Alpha = TimeElapsed / TotalTime;

	if (PingPongActor)
	{
		FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);
		PingPongActor->SetActorLocation(NewLocation);

		if (NewLocation.Equals(TargetLocation, 10.f))
		{
			Exchange(StartLocation, TargetLocation);
			TimeElapsed = 0.f;
		}
	}
	Response.FinishAndTriggerIf(bComplete || Alpha >= 1.f, ExecutionFunction, OutputLink, CallbackTarget);
}
