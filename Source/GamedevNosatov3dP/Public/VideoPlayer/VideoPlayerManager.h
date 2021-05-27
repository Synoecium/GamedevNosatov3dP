// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MediaSource.h"
#include "MediaPlaylist.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "VideoConfig.h"
#include "UObject/NoExportTypes.h"
#include "VideoPlayerManager.generated.h"

/**
 * Video Player Manager responsible for playing videos in the world
 * Requirements
 * tag : VideoPlayer on Actor
 */
UCLASS()
class GAMEDEVNOSATOV3DP_API UVideoPlayerManager : public UObject
{
	GENERATED_BODY()

public:

	DECLARE_EVENT(UVideoPlayerManager, FShowEnded)
	FShowEnded& OnShowEnded() { return _ShowEventEnded;}

	virtual void Init(TSubclassOf<UVideoConfig> VideoConfigClass);

	virtual void PlayVideo();

	virtual void LoadTestVideoResources();

	virtual void PlayTestVideo();

private:

	float Alpha = 0.f;
	
	UPROPERTY()
	UMediaPlayer* _CurrentVideoPlayer;

	UPROPERTY()
	UMediaSource* _CurrentMediaSource;

	UPROPERTY()
	UMediaPlaylist* _CurrentPlaylist;

	UPROPERTY()
	UMediaTexture* _CurrentVideoTexture;

	UPROPERTY()
	UVideoConfig* _CurrentConfig;

	TWeakObjectPtr<AActor> _CurrentVideoPlayerActor;

	FTimerHandle _CurrentTimer;
	
	FShowEnded _ShowEventEnded;

	UFUNCTION()
	void FadeIn();

	bool FindAndSetVideoActor(UWorld* CurrentWorld);
};
