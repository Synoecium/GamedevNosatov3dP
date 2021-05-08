// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IPlatformFilePak.h"
#include "MapInfoBlueprintFunctionLibrary.h"
#include "UObject/NoExportTypes.h"
#include "DLCLoader.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UDLCLoader : public UObject
{
	GENERATED_BODY()

public:
	bool ReadStudiosInfo();

	TArray<FMapInfo> GetMapsInfo();

	void Clear();

private:

	TArray<FString> GetClassesToLoad();

	UPROPERTY()
	TArray<FMapInfo> _mapsInfo;

	TArray<FString> LoadDLC();

	// DLC methods
	bool MountDLC(const FString& PakFilename);
	bool UnmountDLC(const FString& PakFilename);
	int32 GetDLCOrder(const FString& PakFilepath);

	void RegisterMountPoint(const FString& RootPath, const FString& ContentPath);

	TArray<FString> GetFilesInDLC(const FString& DIrectory);
	bool ReadPakFile(FString PakFilename);
	UClass* LoadClassFromDLC(const FString& Filename);

	FPakPlatformFile* GetDLCFile();
	
	FPakPlatformFile* DLCFile;
};
