// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamedevNosatov3dPGameMode.generated.h"

class UBaseCoreConfig;

UCLASS(minimalapi)
class AGamedevNosatov3dPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGamedevNosatov3dPGameMode();

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
	TSubclassOf<UBaseCoreConfig> ConfigurationClass;

	UPROPERTY()
	UBaseCoreConfig* Base_ConfRef;

	virtual void BeginPlay() override;
};



