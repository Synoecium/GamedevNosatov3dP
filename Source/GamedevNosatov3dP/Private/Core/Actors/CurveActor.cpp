// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/CurveActor.h"

#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACurveActor::ACurveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Open = false;
	ReadyState = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACurveActor::BeginPlay()
{
	Super::BeginPlay();

	//RotateValue = 1.f;
	RotateValue = RotateAngle;

	if (DoorCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlDoor"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetState"));

		MyTimeline = NewObject<UTimelineComponent>(this, FName("DoorAnimation"));
		MyTimeline->AddInterpFloat(DoorCurve, TimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		MyTimeline->RegisterComponent();
	}
	
}

// Called every frame
void ACurveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyTimeline != nullptr)
	{
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ACurveActor::ControlDoor()
{
	TimelineValue = MyTimeline->GetPlaybackPosition();
	CurveFloatValue = RotateValue * DoorCurve->GetFloatValue(TimelineValue);

	FQuat NewRotation = FQuat(FRotator(0.f, CurveFloatValue, 0.f));
	//UE_LOG(LogTemp, Warning, TEXT("ControlDoor, TimelineValue = %f, CurveFloatValue = %f"), TimelineValue, CurveFloatValue);

	Door->SetRelativeRotation(NewRotation);
}

void ACurveActor::ToogleDoor()
{
	if (ReadyState)
	{
		Open = !Open;

		// alternative way to get pawn position
		// GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()
		APawn* OurPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		FVector PawnLocation = OurPawn->GetActorLocation();
		FVector Direction = GetActorLocation() - PawnLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

		if (Open)
		{
			if (Direction.X > 0.f)
			{
				RotateValue = RotateAngle;
			}
			else
			{
				RotateValue = -RotateAngle;
			}

			ReadyState = false;
			if (MyTimeline != nullptr)
			{
				MyTimeline->PlayFromStart();
			}
		}
		else
		{
			ReadyState = false;
			if (MyTimeline != nullptr)
			{
				MyTimeline->Reverse();
			}
		}
	}
}

void ACurveActor::SetState()
{
	ReadyState = true;
}

