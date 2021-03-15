// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CoreHelperLibrary.h"

#include "Kismet/GameplayStatics.h"


ABaseGameModeBase* UCoreHelperLibrary::GetBaseGameMode(const UObject* WorldContextObject) 
{
    ABaseGameModeBase* mode = nullptr;
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if (World == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("world is null"));
        return mode;
    }
    mode = Cast<ABaseGameModeBase>(World->GetAuthGameMode());

    return mode;
}
