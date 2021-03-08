// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../GamedevNosatov3dPGameMode.h"
#include "CoreHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UCoreHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static AGamedevNosatov3dPGameMode* GetBaseGameMode(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
    //static AGamedevNosatov3dPGameMode* GetBaseGameMode(UObject* WorldContextObject);

	//UFUNCTION(BlueprintPure)
	//static AGamedevNosatov3dPGameMode* GetBaseGameMode(UObject* parAnyObject);
};
