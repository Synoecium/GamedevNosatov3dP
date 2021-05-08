// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/PrimaryAssetLabel.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MapInfoBlueprintFunctionLibrary.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FMapInfo
{
	GENERATED_BODY()

	FString GetLevelName() const { return FString(); };
	FText GetLevelDescription() const { return FText();};
	FString GetLevelReference() { return FString();};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText _name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText _description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSoftObjectPath _primaryAsset;

	UPROPERTY()
	UPrimaryAssetLabel* _primaryAssetLabel;
	
};

UCLASS()
class GAMEDEVNOSATOV3DP_API UMapInfoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*Blueprint function to return the value from the struct*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MapInfo|Methods")
	static FString GetLevelReference(UPARAM(ref) FMapInfo& MyStructRef) { return MyStructRef.GetLevelReference(); };
};

UCLASS(BlueprintType, Blueprintable)
class UMapInfoAsset : public UObject
{
	GENERATED_BODY()
public:
	UMapInfoAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
	{
		
	}

	UPROPERTY(EditAnywhere)
	FMapInfo _mapInfo;
};
