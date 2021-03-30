// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "Actors/BaseUnit.h"
#include "Core/Configs/BaseUnitConfig.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameModeBase.generated.h"

class UBaseCoreConfig;

UCLASS(minimalapi)
class ABaseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseGameModeBase();

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
};






