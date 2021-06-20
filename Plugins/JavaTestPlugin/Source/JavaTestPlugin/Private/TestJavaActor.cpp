// Fill out your copyright notice in the Description page of Project Settings.


#include "TestJavaActor.h"

#include "JavaCaller.h"

// Sets default values
ATestJavaActor::ATestJavaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestJavaActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestJavaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestJavaActor::TestJavaCall()
{
	UJavaCaller::CallJavaCode();
}

void ATestJavaActor::JavaTakePhoto()
{
	UJavaCaller::CallTakePhoto();
}
