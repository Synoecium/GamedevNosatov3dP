// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/BaseGameModeBase.h"
#include "GamedevNosatov3dPCharacter.h"
#include "PawnTurret.h"
#include "Core/PawnBase.h"
#include "Core/Actors/BaseBuilding.h"
#include "Core/Controllers/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#endif


ABaseGameModeBase::ABaseGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	AmountOfMoney = 100;
	bEnableDance = false;
	DialogMessage = "Hello, I love dancing!";
	Base_ConfRef = nullptr;
	Score = 0.f;
}

bool ABaseGameModeBase::SpawnUnit(AActor*& parActor) 
{
	UWorld* CurrentWorld = GetWorld();

	if (CurrentWorld && Unit) 
	{
		parActor = CurrentWorld->SpawnActor<AActor>(Unit);
		UE_LOG(LogTemp, Warning, TEXT("Spawn actor: %s"), *parActor->GetName());		
		BP_UpdateInfo();		 
		return true;
	}

	return false;
}

void ABaseGameModeBase::Init_Implementation() 
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Init c++ Native Event"));
}

void ABaseGameModeBase::BeginPlay() 
{
	Super::BeginPlay();

	UWorld* CurrentWorld = GetWorld();
	CurrentWorld->GetFirstPlayerController()->Destroy();
	for(TActorIterator<AActor>Itr(CurrentWorld);Itr;++Itr)
	{
		if (Cast<ABaseBuilding>(*Itr))
		{
			ABaseBuilding* CurrentBarracks = Cast<ABaseBuilding>(*Itr);
			CurrentBarracks->OnSpawnUnit().AddUObject(this, &ABaseGameModeBase::OnUnitCreated);
		}
	}

	

	//UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %i"), AmountOfMoney);

	for (auto& str : Names)
	{
		//UE_LOG(LogTemp, Warning, TEXT("I've runned from Actor called: %s"), *str);
	}

	if (ConfigurationClass)
	{
		Base_ConfRef = NewObject<UBaseUnitConfig>(this,ConfigurationClass);
		/*UE_LOG(LogTemp, Warning, TEXT("This is my log value 1: %i"), Base_ConfRef->ConfigValue1);
		UE_LOG(LogTemp, Warning, TEXT("This is my log value 2: %i"), Base_ConfRef->ConfigValue2);
		UE_LOG(LogTemp, Warning, TEXT("This is my log value 3: %i"), Base_ConfRef->ConfigValue3);*/
	}
	//PZ #5 start
	TArray<AActor*> turretActors;
	UGameplayStatics::GetAllActorsOfClass(this, APawnTurret::StaticClass(), turretActors);
	for (AActor* turretActor:turretActors)
	{
		APawnTurret* turret = Cast<APawnTurret>(turretActor);
		if (turret)
		{
			turret->OnPawnKilled.AddUFunction(this, "OnTurretKilled");
		}
	}
	//PZ #5 finish
	
	Init();
}

//PZ #5 start
void ABaseGameModeBase::OnTurretKilled()
{
	Score+=ScoreForKillTurret;
}
//PZ #5 finish

//PZ #6 start
void ABaseGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Post Login GameMode"));
	LoadAmmoFromFile(TEXT("Ammo.sav"));
}

void ABaseGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	UE_LOG(LogTemp, Warning, TEXT("Logout GameMode"));
	SaveAmmoToFile(TEXT("Ammo.sav"));
}

void ABaseGameModeBase::OnUnitCreated(ABaseUnit* parUnit)
{
	ABasePlayerController* Controller = GetWorld()->SpawnActor<ABasePlayerController>();
	//Controller->InputComponent = NewObject<UInputComponent>(Controller);

	if (PlayerControllerIndex == 0)
	{/*
		FInputChord Ch(EKeys::Up, EInputEvent::IE_Pressed);
		Controller->SetupInputComponent();
		Controller->InputComponent->BindKey(Ch, IE_Released, Controller, &ABasePlayerController::OnKeyPressed);*/
		SavedInputComponent = NewObject<UInputComponent>(Controller);
		Controller->InputComponent = SavedInputComponent;
		FInputChord Ch(EKeys::W,EInputEvent::IE_Pressed);
		parUnit->AutoPossessPlayer = EAutoReceiveInput::Player0;
		Controller->AutoReceiveInput = EAutoReceiveInput::Player0;
		Controller->InitInputSystem();
		Controller->InputComponent->BindKey(Ch,EInputEvent::IE_Released,Controller,&ABasePlayerController::OnKeyPressed);
	}
	if (PlayerControllerIndex > 0)
	{
		Controller->InputComponent = SavedInputComponent;
		FInputChord Ch(EKeys::S,EInputEvent::IE_Pressed);
		parUnit->AutoPossessPlayer = EAutoReceiveInput::Player1;
		Controller->EnableInput(Controller);
		Controller->AutoReceiveInput = EAutoReceiveInput::Player1;
		Controller->InitInputSystem();
		
		Controller->InputComponent->BindKey(Ch,EInputEvent::IE_Released,Controller,&ABasePlayerController::OnKeyPressed);	
	}

	//UEditorEngine* EnginePtr = Cast<UEditorEngine>(GEngine);

	TIndirectArray<FWorldContext> GetWorldContexts = GEngine->GetWorldContexts();
	UWorld* World = GetWorldContexts.Last().World();
	FString Error;
	TArray<ULocalPlayer*> Players = World->GetGameInstance()->GetLocalPlayers();

	if(PlayerControllerIndex == 0)
		World->GetGameInstance()->RemoveLocalPlayer(Players.Last());
	
	ULocalPlayer* LocalPlayer = World ? World->GetGameInstance()->CreateLocalPlayer(PlayerControllerIndex, Error, false) : nullptr;
	LocalPlayer->SwitchController(Controller);
	Controller->InputComponent->ConditionalBuildKeyMap(Controller->PlayerInput);
	Controller->Possess(parUnit);
	
	PlayerControllerIndex++;
}

void ABaseGameModeBase::SaveAmmoToFile(FString FileName)
{
	UE_LOG(LogTemp, Warning, TEXT("Saving ammo..."));
	int32 CurrentAmmo = GetAmmoCount();
	
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString SaveDirectory = FPaths::ProjectContentDir();
	FString FilePath = SaveDirectory + "/" + FileName;
	UE_LOG(LogTemp, Warning, TEXT("File path: %s"), *FilePath);
	IFileHandle* FileHandle = PlatformFile.OpenWrite(*FilePath);
	if(FileHandle)
	{
		int32* IntPointer = &CurrentAmmo;
		uint8* ByteBuffer = reinterpret_cast<uint8*>(IntPointer);
		// Write the bytes to the file
		FileHandle->Write(ByteBuffer, sizeof(int32));
		// Close the file again
		delete FileHandle;       
    }
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot open file to write"));
	}

}

void ABaseGameModeBase::LoadAmmoFromFile(FString FileName)
{
	UE_LOG(LogTemp, Warning, TEXT("Loading ammo..."));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString SaveDirectory = FPaths::ProjectContentDir();
	FString FilePath = SaveDirectory + "/" + FileName;
	UE_LOG(LogTemp, Warning, TEXT("File path: %s"), *FilePath);
	IFileHandle* FileHandle = PlatformFile.OpenRead(*FilePath);
	if(FileHandle)
	{
		int32 CurrentAmmo = 0; 
		// Create a pointer to MyInteger
		int32* IntPointer = &CurrentAmmo;
		// Reinterpret the pointer for the Read function
		uint8* ByteBuffer = reinterpret_cast<uint8*>(IntPointer);
        
		// Read the integer from file into our reinterpret pointer
        FileHandle->Read(ByteBuffer, sizeof(int32));
		// Because ByteBuffer points directly to MyInteger, it's already been updated at this point

        // Close the file again
        delete FileHandle;

		SetAmmoCount(CurrentAmmo);
		UE_LOG(LogTemp, Warning, TEXT("New ammo value = %d"), CurrentAmmo);
	}
}

int32 ABaseGameModeBase::GetAmmoCount() const
{
	return AmmoCount;
}

void ABaseGameModeBase::SetAmmoCount(int32 NewCount)
{
	AmmoCount = NewCount;
}
//PZ #6 finish
