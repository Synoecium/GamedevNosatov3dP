// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

USTRUCT()
struct FDamageParams
{
	GENERATED_BODY()

	UPROPERTY()
	float DamageValue;	
	UPROPERTY()
	AActor* DamageMaker;	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEDEVNOSATOV3DP_API IDamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//DamageInterface.h
	virtual void ApplyDamage(FDamageParams DamageParams) = 0;
};
