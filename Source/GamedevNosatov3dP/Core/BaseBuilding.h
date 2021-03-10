// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseUnit.h"
#include "GameFramework/Actor.h"
#include "BaseBuilding.generated.h"

class UBaseUnitConfig;

UCLASS()
class GAMEDEVNOSATOV3DP_API ABaseBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuilding();

	DECLARE_EVENT_OneParam(ABaseBuilding, FOnSpawnUnit, ABaseUnit*)
	FOnSpawnUnit& OnSpawnUnit()
	{
		return OnSpawnUnitChanged;
	}

	UPROPERTY(EditAnywhere, Category = "Unit Config")
	TSubclassOf<UBaseUnitConfig> UnitConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* BaseSpawnPont;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;

	UFUNCTION(BlueprintCallable)
	void SpawnUnit();

	UFUNCTION()
	static ABaseUnit* Create_Unit(UBaseUnitConfig* config); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UBaseUnitConfig* CurrentUnitConfig;

	FOnSpawnUnit OnSpawnUnitChanged;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
