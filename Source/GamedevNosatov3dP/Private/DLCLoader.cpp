// Fill out your copyright notice in the Description page of Project Settings.


#include "DLCLoader.h"

//#include <shobjidl_core.h>

#include "Engine/AssetManager.h"

bool UDLCLoader::ReadStudiosInfo()
{
#if UE_BUILD_SHIPPING
	//
#else

	UAssetManager* assetManager = &UAssetManager::Get();

	TArray<FString> classesToLoad = GetClassesToLoad();

	TArray<FAssetData> RegistryData;

	if (assetManager->GetAssetRegistry().GetAllAssets(RegistryData))
	{
		for (FAssetData& data : RegistryData)
		{
			//FString AssetName = data.AssetName.TOString();
			//*		data.PrintAssetData();*/
			for (FString classToLoad : classesToLoad)
			{
				if (data.AssetName == FName(*classToLoad))
				{
					UObject* objectToLoad = nullptr;
					auto generatedClassPath = data.TagsAndValues.FindTag(FName("GeneratedClass"));
					if (generatedClassPath.IsSet())
					{
						//Convert path to just the name part
						const FString ClassObjectPath = FPackageName::ExportTextPathToObjectPath(*generatedClassPath.GetValue());
						const FString ClassName = FPackageName::ObjectPathToObjectName(ClassObjectPath);
						// CHeck if this class is in the derived set
						// Store using the path to the generated class
						objectToLoad = FStringAssetReference(ClassObjectPath).TryLoad();
					}
					if (objectToLoad)
					{
						UBlueprintGeneratedClass* generatedClass = Cast<UBlueprintGeneratedClass>(objectToLoad);
						UMapInfoAsset* mapInfoObject = Cast<UMapInfoAsset>(generatedClass->GetDefaultObject());
						if (mapInfoObject)
						{
							_mapsInfo.Add(mapInfoObject->_mapInfo);
						}
					}
				}
			}
		}
	}

#endif
	
	LoadDLC();

	return _mapsInfo.Num() > 0;
	//return true;
}

TArray<FMapInfo> UDLCLoader::GetMapsInfo()
{
	if (_mapsInfo.Num() == 0)
	{
		ReadStudiosInfo();
	}
	return _mapsInfo;
}

void UDLCLoader::Clear()
{
	_mapsInfo.Empty();
}

TArray<FString> UDLCLoader::GetClassesToLoad()
{
	TArray<FString> outClasses;

	TArray<FName> baseClasses;
	TSet<FName> excludedClasses;
	TSet<FName> derivedClasses;
	baseClasses.Add(UMapInfoAsset::StaticClass()->GetFName());
	UAssetManager* assetManager = &UAssetManager::Get();
	assetManager->GetAssetRegistry().GetDerivedClassNames(baseClasses, excludedClasses, derivedClasses);

	for (FName derived : derivedClasses)
	{
		/*Trim class name to get ClassName instead of ClassName.ClassName_C*/
		FString derivedString = derived.ToString();
		if (derivedString.EndsWith("_C"))
			derivedString = derivedString.Mid(0, derivedString.Len() - 2);

		outClasses.Add(*derivedString);
	}
	return outClasses;
}

// DLC Loading
// 1. Search dlc *.pak files in <GameFolder>/DLC/" path
// 2. *pak's name must be equivalently to plugin name
// 3. Use PakLoader plugin for load and mount plugins
//
// Return: array of loaded plugin's names
TArray<FString> UDLCLoader::LoadDLC()
{
	TArray<FString> LoadedPlugins;
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Run in Editor mode. DLC loading aborted"));
	return LoadedPlugins;
#endif
	//Get DLC folder
	FString PathToDLCFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir())+"DLC";
	PathToDLCFolder = "e:/.../Plugins/Chapter2/Content/Paks/WindowsNoEditor";
	UE_LOG(LogTemp, Warning, TEXT(" PATH: %s "), *PathToDLCFolder);
	IFileManager& FileManager = IFileManager::Get();

	if (!FPaths::DirectoryExists(PathToDLCFolder))
	{
		UE_LOG(LogTemp, Warning, TEXT("DLC directory %s not found"), *PathToDLCFolder);
		FileManager.MakeDirectory(*PathToDLCFolder, true);
		return LoadedPlugins;
	}

	//Get all *pak files and try to load plugins
	TArray<FString> PAKFiles;
	FString DLCExtension = "*.pak";
	FileManager.FindFilesRecursive(PAKFiles, *PathToDLCFolder, *DLCExtension, true, false);

	for (size_t i = 0; i < PAKFiles.Num(); i++)
	{
		MountDLC(PAKFiles[i]);
		ReadPakFile(PAKFiles[i]);
	}
	return LoadedPlugins;
}

bool UDLCLoader::MountDLC(const FString& PakFilename)
{
	int32 PakOrder = GetDLCOrder(PakFilename);
	FPakPlatformFile* dlcFile = GetDLCFile();
	TArray<FString> mountedPoints1;
	dlcFile->GetMountedPakFilenames(mountedPoints1);

	bool result = dlcFile->Mount(*PakFilename, PakOrder, NULL);
	TArray<FString> mountedPoints2;
	dlcFile->GetMountedPakFilenames(mountedPoints2);
	
	return result;
}

bool UDLCLoader::UnmountDLC(const FString& PakFilename)
{
	int32 PakOrder = GetDLCOrder(PakFilename);
	FPakPlatformFile* dlcFile = GetDLCFile();
	TArray<FString> mountedPoints1;
	dlcFile->GetMountedPakFilenames(mountedPoints1);

	if (mountedPoints1.Contains(PakFilename))
	{
		UE_LOG(LogTemp, Warning, TEXT("Mount point %s exists! Unmount started..."), *PakFilename);
		if (dlcFile->Unmount(*PakFilename))
		{
			UE_LOG(LogTemp, Warning, TEXT("Unmounted!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unmounting error!"));
			return false;
		}
	}
	return true;
}

int32 UDLCLoader::GetDLCOrder(const FString& PakFilepath)
{
	if (PakFilepath.StartsWith(FString::Printf(TEXT("%sPaks/%s-"), *FPaths::ProjectContentDir(), FApp::GetProjectName())))
	{
		return 4;
	}
	else if (PakFilepath.StartsWith(FPaths::ProjectContentDir()))
	{
		return 3;
	}
	else if (PakFilepath.StartsWith(FPaths::EngineContentDir()))
	{
		return 2;
	}
	else if (PakFilepath.StartsWith(FPaths::ProjectSavedDir()))
	{
		return 1;
	}

	return 0;
}

void UDLCLoader::RegisterMountPoint(const FString& RootPath, const FString& ContentPath)
{
}

TArray<FString> UDLCLoader::GetFilesInDLC(const FString& DIrectory)
{
	return TArray<FString>();
}

bool UDLCLoader::ReadPakFile(FString PakFilename)
{
	UE_LOG(LogTemp, Warning, TEXT("ReadPakFile: Mount pak file : %s"), *PakFilename);

	FPakPlatformFile* PakPlatformFile;
	{
		FString PlatformFileName = FPlatformFileManager::Get().GetPlatformFile().GetName();
		if (PlatformFileName.Equals(FString(TEXT("PakFile"))))
		{
			PakPlatformFile = static_cast<FPakPlatformFile*>(&FPlatformFileManager::Get().GetPlatformFile());
		}
		else
		{
			PakPlatformFile = new FPakPlatformFile;
			if (!PakPlatformFile->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), TEXT("")))
			{
				UE_LOG(LogTemp, Error, TEXT("FPakPlatformFile failed to initialize"));
				return false;
			}
			FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);
		}
	}

	FString PakFilePathFull = FPaths::ConvertRelativePathToFull(PakFilename);
	FPakFile PakFile(PakPlatformFile, *PakFilePathFull, false);
	TArray<FString> FileList;
	FString packName = FPaths::GetBaseFilename(PakFilename);
	FString MountPoint = PakFile.GetMountPoint();
	PakFile.FindFilesAtPath(FileList, *MountPoint, true, false, true);

	FStreamableManager StreamableManager;

	for (int32 k = 0; k < FileList.Num(); k++)
	{
		FString AssetName = FileList[k];
		if (AssetName.Contains("BP_") && AssetName.Contains(".uasset"))
		{
			UE_LOG(LogTemp, Log, TEXT("Loading Pak: %s from File %s ..."), *packName, *FileList[k]);

			FString AssetShortName = FPackageName::GetShortName(AssetName);
			FString FileName, FileExt;
			AssetShortName.Split(TEXT("."), &FileName, &FileExt);
			FString NewAssetName = FString("/") + packName + "/" + FileName + TEXT(".") + FileName + "_C";
			UE_LOG(LogTemp, Log, TEXT("Loading Asset %s ..."), *NewAssetName);

			UObject* objectToLoad = nullptr;
			FStringAssetReference ref = FStringAssetReference(NewAssetName);
			UE_LOG(LogTemp, Warning, TEXT("Loading object ..."));
			objectToLoad = ref.TryLoad();

			if (objectToLoad)
			{
				UBlueprintGeneratedClass* GeneratedClass = Cast<UBlueprintGeneratedClass>(objectToLoad);
				UMapInfoAsset* mapInfoObject = Cast<UMapInfoAsset>(GeneratedClass->GetDefaultObject());
				// Take default object be "info" class
				if (mapInfoObject)
				{
					_mapsInfo.Add(mapInfoObject->_mapInfo);
					UE_LOG(LogTemp, Warning, TEXT("Add data %s"), *mapInfoObject->GetFullName());
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("File %s loading error!"), *FileList[k]);
				}
			}
		}
	}
	return true;
}

UClass* UDLCLoader::LoadClassFromDLC(const FString& Filename)
{
	return nullptr;
}

FPakPlatformFile* UDLCLoader::GetDLCFile()
{
	if (!DLCFile)
	{
		IPlatformFile* CurrentPlatformFile = FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile"));
		if (CurrentPlatformFile)
		{
			DLCFile = static_cast<FPakPlatformFile*>(CurrentPlatformFile);
		}
		else
		{
			DLCFile = new FPakPlatformFile();
			ensure(DLCFile != nullptr);
			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

#if UE_BUILD_SHIPPING == 0
			auto OriginalPlatformFile = &PlatformFile;
#endif
			if (DLCFile->Initialize(&PlatformFile, TEXT("")))
			{
				FPlatformFileManager::Get().SetPlatformFile(*DLCFile);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("DLCFile initialization error!"));
			}
		}
	}

	ensure(DLCFile != nullptr);
	return DLCFile;
}
