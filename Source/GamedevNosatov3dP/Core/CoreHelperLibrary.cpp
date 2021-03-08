// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreHelperLibrary.h"

#include "Kismet/GameplayStatics.h"


AGamedevNosatov3dPGameMode* UCoreHelperLibrary::GetBaseGameMode(const UObject* WorldContextObject) 
{
    AGamedevNosatov3dPGameMode* mode = nullptr;
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
    if (World == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("world is null"));
        return mode;
    }
    mode = Cast<AGamedevNosatov3dPGameMode>(World->GetAuthGameMode());

    return mode;
}
