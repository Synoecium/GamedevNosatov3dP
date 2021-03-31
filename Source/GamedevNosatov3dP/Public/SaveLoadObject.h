// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveLoadObject.generated.h"

/**
 * 
 */

USTRUCT()
struct FObjectData
{
	GENERATED_BODY()

public:
	TArray<uint8> Data;	
};

USTRUCT()
struct FPawnData : public FObjectData
{
	GENERATED_BODY()

public:
	FVector Position;
	FRotator Rotation;

	friend FArchive& operator<<(FArchive& Ar, FPawnData& PawnData)
	{
		Ar<<PawnData.Data;
		Ar<<PawnData.Position;
		Ar<<PawnData.Rotation;
		return Ar;
	}
};

USTRUCT()
struct FControllerData : public FObjectData
{
	GENERATED_BODY()

public:
	FRotator Rotation;

	friend FArchive& operator<<(FArchive& Ar, FControllerData& ControllerData)
	{
		Ar<<ControllerData.Data;
		Ar<<ControllerData.Rotation;
		return Ar;
	}
};

USTRUCT()
struct FData
{
	GENERATED_BODY()
public:
	FPawnData Pawn;
	FControllerData Controller;
	
	friend FArchive& operator<<(FArchive& Ar, FData& Data)
	{
		Ar<<Data.Pawn;
		Ar<<Data.Controller;
		return Ar;
	}
};

UCLASS()
class GAMEDEVNOSATOV3DP_API USaveLoadObject : public UObject
{
	GENERATED_BODY()

public:
	void SaveCharacter(class APlayerController* CharacterToSave);
	void LoadCharacter(class APlayerController* CharacterToLoad);
	
};
