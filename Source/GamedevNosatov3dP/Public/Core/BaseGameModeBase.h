// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "Actors/BaseUnit.h"
#include "Core/Configs/BaseUnitConfig.h"
#include "GameFramework/GameModeBase.h"
#include "UI/MainMenuWidget.h"

#include "BaseGameModeBase.generated.h"

class UBaseCoreConfig;
class TCPClient;

USTRUCT(BlueprintType)
struct FUserDataGD
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	int32 Scores;

};

	
UCLASS(minimalapi)
class ABaseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseGameModeBase();
	~ABaseGameModeBase();

	UPROPERTY(EditAnyWhere, Category = "Bank | Money | USD")
	int32 AmountOfMoney;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bEnableDance;

	UPROPERTY(EditAnyWhere)
	FString DialogMessage;

	UPROPERTY(EditAnyWhere)
	TArray<FString> Names;

	UPROPERTY(EditAnyWhere)
	TSubclassOf<AActor> Unit;

	UFUNCTION(BlueprintCallable)
	bool SpawnUnit(UPARAM(ref) AActor*& parActor);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateInfo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Init();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBaseUnitConfig> ConfigurationClass;

	UPROPERTY()
	UBaseUnitConfig* Base_ConfRef;

	//PZ #5 start		
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTurretKilled();

	UFUNCTION(BlueprintPure)
	float GetScore() const {return Score;};
	//PZ #5 finish

	//PZ #6 start
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UFUNCTION(BlueprintPure)
	int32 GetAmmoCount() const;
	
	UFUNCTION(BlueprintCallable)
    void SetAmmoCount(int32 NewCount);

	UPROPERTY(EditAnyWhere)
	int32 AmmoCount = 1;
	//PZ #6 finish

	UPROPERTY(EditAnyWhere)
	float ScoreForKillTurret = 50.f;

	int32 PlayerControllerIndex = 0;
	
	UFUNCTION()
	void OnUnitCreated(ABaseUnit* parUnit);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget> MainMenuClass;

	UFUNCTION(BlueprintCallable)
	void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);
	
	UFUNCTION(BlueprintCallable)
	void SetImageFileAsTexture(AActor* TargetActor, const FString& Filename);

	UFUNCTION(BlueprintCallable)
	void SavePlayerResult(FString PlayerName, int32 Scores);

	UFUNCTION(BlueprintCallable)
	TArray<FUserDataGD> GetUserData();

protected:
	//PZ #5 start
	float Score;
	//PZ #5 finish

	//PZ #6 start
	void SaveAmmoToFile(FString FileName);
	void LoadAmmoFromFile(FString FileName);
	//PZ #6 finish

	UPROPERTY(EditAnyWhere)
	UInputComponent* SavedInputComponent;

	TCPClient* client = nullptr;
	TArray<unsigned char> Buff;
	bool WriteInt(int32 Value);
	bool WriteString(FString Value);
	bool WriteBytes(unsigned char* Data, int32 Size);
	int32 ReadInt(TArray<uint8> Data);
	FString ReadString(TArray<uint8> Data);
	
};






