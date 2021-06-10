// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QueryItem.generated.h"

UCLASS()
class GAMEDEVNOSATOV3DP_API AQueryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQueryItem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ValueOfItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
