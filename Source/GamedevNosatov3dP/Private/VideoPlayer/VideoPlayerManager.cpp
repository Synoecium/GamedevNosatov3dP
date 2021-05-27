// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoPlayer/VideoPlayerManager.h"

#include "EngineUtils.h"
#include "MediaSoundComponent.h"

void UVideoPlayerManager::Init(TSubclassOf<UVideoConfig> VideoConfigClass)
{
	_CurrentConfig = NewObject<UVideoConfig>(this, VideoConfigClass);
	_CurrentVideoPlayer = NewObject<UMediaPlayer>(this);
}

void UVideoPlayerManager::PlayVideo()
{

}

void UVideoPlayerManager::LoadTestVideoResources()
{
	_CurrentVideoTexture = LoadObject<UMediaTexture>(nullptr, *_CurrentConfig->PathToVideoTexture);
	_CurrentMediaSource = LoadObject<UMediaSource>(nullptr, *_CurrentConfig->PathToMediaSource);
	_CurrentPlaylist = LoadObject<UMediaPlaylist>(nullptr, *_CurrentConfig->PathToPlaylist);
#if WITH_EDITOR
	_CurrentVideoTexture->SetDefaultMediaPlayer(_CurrentVideoPlayer);
#endif
}

void UVideoPlayerManager::PlayTestVideo()
{
	if (_CurrentPlaylist)
	{
		_CurrentVideoPlayer->OpenPlaylist(_CurrentPlaylist);
	}
	else
	{
		_CurrentVideoPlayer->OpenSource(_CurrentMediaSource);
	}
	
	_CurrentVideoPlayer->Play();
	
	_CurrentVideoPlayer->SetLooping(true);

	UGameInstance* GI = Cast<UGameInstance>(GetOuter());
	UWorld* CurrentWorld = GI->GetWorld();

	if (CurrentWorld)
	{
		bool isMediaPlayerExist = FindAndSetVideoActor(CurrentWorld);
		if (isMediaPlayerExist)
		{
			CurrentWorld->GetTimerManager().SetTimer(_CurrentTimer, this, &UVideoPlayerManager::FadeIn, 0.01f, true);
			if (_CurrentVideoPlayerActor.IsValid())
			{
				auto MScomp = Cast<UMediaSoundComponent>(_CurrentVideoPlayerActor->GetComponentByClass(UMediaSoundComponent::StaticClass()));
				if (MScomp)
					if (_CurrentPlaylist)
					{
						MScomp->GetMediaPlayer()->OpenPlaylist(_CurrentPlaylist);
					}
					else
					{
						MScomp->GetMediaPlayer()->OpenSource(_CurrentMediaSource);
					}			
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UVideoPlayerManager::World doesn't exist, check the call"))
	}

}

void UVideoPlayerManager::FadeIn()
{
	if (!_CurrentVideoPlayerActor->GetActorLocation().Equals(_CurrentConfig->EndPosition, 100.f))
	{
		FVector Pos = FMath::Lerp(_CurrentConfig->StartPosition, _CurrentConfig->EndPosition, Alpha += 0.001f);
		_CurrentVideoPlayerActor->SetActorLocation(Pos);
	}
	else
	{
		UGameInstance* GI = Cast<UGameInstance>(GetOuter());
		UWorld* CurrentWorld = GI->GetWorld();

		if (CurrentWorld)
		{
			_ShowEventEnded.Broadcast();
			CurrentWorld->GetTimerManager().ClearTimer(_CurrentTimer);
		}
	}
}

bool UVideoPlayerManager::FindAndSetVideoActor(UWorld* CurrentWorld)
{
	for (TActorIterator<AActor> ActorItr(CurrentWorld); ActorItr; ++ActorItr)
	{
		AActor* temp = *ActorItr;
		if (temp->ActorHasTag(_CurrentConfig->TagSearchName))
		{
			_CurrentVideoPlayerActor = temp;
			return true;
		}
	}
	return false;
}
