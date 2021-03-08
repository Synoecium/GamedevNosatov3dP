// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseCoreConfig.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GAMEDEVNOSATOV3DP_API UBaseCoreConfig : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int32 ConfigValue1 = 112;
	UPROPERTY(EditAnywhere)
	int32 ConfigValue2 = 113;
	UPROPERTY(EditAnywhere)
	int32 ConfigValue3 = 114;
};
