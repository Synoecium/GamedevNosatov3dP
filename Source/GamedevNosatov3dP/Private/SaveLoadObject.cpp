// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadObject.h"
#include "GamedevNosatov3dPCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Misc/FileHelper.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void USaveLoadObject::SaveCharacter(APlayerController* CharacterToSave)
{
	if (!CharacterToSave) return;
	//if (!CharacterToSave->Implements<USaveable>()) return;

	FControllerData ControllerData;
	FPawnData PawnData;
	if (ISaveable* SaveableObject = Cast<ISaveable>(CharacterToSave))
	{
		SaveableObject->PreSaved();
		
		FMemoryWriter MemoryArchive(ControllerData.Data, true);
		FObjectAndNameAsStringProxyArchive Ar(MemoryArchive, true);
		Ar.ArIsSaveGame = true;
		Ar.ArNoDelta = true;
		CharacterToSave->Serialize(Ar);

		ControllerData.Rotation = CharacterToSave->GetControlRotation();		
		
		SaveableObject->Saved();
	}

	if (APawn* Pawn = CharacterToSave->GetPawn())
	{
		
		if (ISaveable* SaveableObject = Cast<ISaveable>(Pawn))
		{
			SaveableObject->PreSaved();
		
			FMemoryWriter MemoryArchive(PawnData.Data, true);
			FObjectAndNameAsStringProxyArchive Ar(MemoryArchive, true);
			Ar.ArIsSaveGame = true;
			Ar.ArNoDelta = true;
			Pawn->Serialize(Ar);

			PawnData.Position = Pawn->GetActorLocation();
			PawnData.Rotation = Pawn->GetActorRotation();
		
			SaveableObject->Saved();			
		}
	}

	FData Data;
	Data.Controller = ControllerData;
	Data.Pawn = PawnData;
	
	FBufferArchive Buffer;
	Buffer<<Data;

	TArray<uint8> CompressedData;
	FArchiveSaveCompressedProxy Compressor = FArchiveSaveCompressedProxy(CompressedData, NAME_Zlib);
	if (Compressor.GetError())
		return;

	Compressor << Buffer;
	Compressor.Flush();

	FString Path = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("CharacterData.sav")); 
	FFileHelper::SaveArrayToFile(CompressedData, *Path);
	Compressor.FlushCache();
	CompressedData.Empty();
	Compressor.Close();
	Buffer.Empty();
	Buffer.Close();
}

void USaveLoadObject::LoadCharacter(APlayerController* CharacterToLoad)
{
	if (!CharacterToLoad) return;

	FString Path = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("CharacterData.sav"));
	if (IFileManager::Get().FileSize(*Path) <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s doesn't exist!"), *Path);
		return;
	}

	TArray<uint8> BinaryData;
	if (!FFileHelper::LoadFileToArray(BinaryData, *Path))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s cannot be loaded!"), *Path);
		return;		
	}

	FArchiveLoadCompressedProxy Decompressor = FArchiveLoadCompressedProxy(BinaryData, NAME_Zlib);
	if (Decompressor.GetError())
		return;

	FBufferArchive Buffer;
	Decompressor << Buffer;

	FMemoryReader MemoryReader = FMemoryReader(Buffer, true);
	MemoryReader.Seek(0);

	FData LoadedData;
	MemoryReader<<LoadedData;

	if (ISaveable* SaveableObject = Cast<ISaveable>(CharacterToLoad))
	{
		SaveableObject->PreLoaded();
		CharacterToLoad->SetControlRotation(LoadedData.Controller.Rotation);
		FMemoryReader ControllerMemoryReader(LoadedData.Controller.Data);
		FObjectAndNameAsStringProxyArchive Ar(ControllerMemoryReader, true);
		CharacterToLoad->Serialize(Ar);
		ControllerMemoryReader.FlushCache();
		ControllerMemoryReader.Close();
		
		SaveableObject->Loaded();		
	}

	if (APawn* Pawn = CharacterToLoad->GetPawn())
	{
		if (ISaveable* SaveableObject = Cast<ISaveable>(Pawn))
		{
			SaveableObject->PreLoaded();
			Pawn->SetActorLocation(LoadedData.Pawn.Position);
			Pawn->SetActorRotation(LoadedData.Pawn.Rotation);
			FMemoryReader PawnMemoryReader(LoadedData.Pawn.Data);
			FObjectAndNameAsStringProxyArchive Ar(PawnMemoryReader, true);
			Pawn->Serialize(Ar);
			PawnMemoryReader.FlushCache();
			PawnMemoryReader.Close();
		
			SaveableObject->Loaded();	
		}
	}
}
