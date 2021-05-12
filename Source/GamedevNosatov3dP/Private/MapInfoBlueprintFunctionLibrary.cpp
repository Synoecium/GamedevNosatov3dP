// Fill out your copyright notice in the Description page of Project Settings.


#include "MapInfoBlueprintFunctionLibrary.h"

#include "PingPongAction.h"

void UMapInfoBlueprintFunctionLibrary::PingPong(AActor* InActor, FVector LocationA, FVector LocationB,
                                                TEnumAsByte<EPingPongStatus> Status, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(InActor))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FPingPongAction* PingPongAction = LatentActionManager.FindExistingAction<FPingPongAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
		if (!PingPongAction)
		{
			if (Status==EPingPongStatus::Start)
			{
				PingPongAction = new FPingPongAction(InActor, LocationA, LocationB, LatentInfo);
				LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, PingPongAction);	
			}
		}
		else if (Status == EPingPongStatus::Stop)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stop PingPong!"));
			PingPongAction->bComplete = true;
		}
	}
}
