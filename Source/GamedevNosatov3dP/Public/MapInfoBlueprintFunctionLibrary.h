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

UENUM()
enum EPingPongStatus
{
	Start = 0, Stop
};

UCLASS()
class GAMEDEVNOSATOV3DP_API UMapInfoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/*Blueprint function to return the value from the struct*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MapInfo|Methods")
	static FString GetLevelReference(UPARAM(ref) FMapInfo& MyStructRef) { return MyStructRef.GetLevelReference(); };

	/*
	 * @param InActor - Actor to ping pong
	 * @param LocationA - Start location
	 * @param LocationB - End Location
	 * @param Status - Status
	 * @param Info Info about the Action in background
	 */
	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject", ExpandEnumAsExecs = "Status"),
		Category = "MasterBFL")
	static void PingPong(AActor* InActor, FVector LocationA, FVector LocationB, TEnumAsByte<EPingPongStatus> Status, FLatentActionInfo LatentInfo);
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
