// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), AdvancedClassDisplay, meta=(BlueprintSpawnableComponent) )
class GAMEDEVNOSATOV3DP_API URandomMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URandomMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

private:
	FVector CurrentDirection;
	float CurrentRandomTime = 0.f;
		
};
