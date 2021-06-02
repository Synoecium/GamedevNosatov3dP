// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamedevNosatov3dPCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MyGameInstance.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Core/BaseGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Core/Gun.h"
#include "Core/Actors/BaseUnit.h"
#include "Net/UnrealNetwork.h"

//////////////////////////////////////////////////////////////////////////
// AGamedevNosatov3dPCharacter

AGamedevNosatov3dPCharacter::AGamedevNosatov3dPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	/*ButtonComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ButtonComponent"));
	ButtonComponent->SetWidgetSpace(EWidgetSpace::World);
	ButtonComponent->SetupAttachment(RootComponent);
	if (ButtonClass)
	{
		UUserWidget* Button = CreateWidget<UUserWidget>(GetWorld(),ButtonClass);
		ButtonComponent->SetWidget(Button);
		
	}*/
	//else GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Button class is empty!"));
	
	//ButtonComponent->SetRelativeLocationAndRotation(FVector(0,0,0),FRotator(0,180,0));

	SetReplicates(true);
}

void AGamedevNosatov3dPCharacter::BeginPlay()
{
	Super::BeginPlay();

	//ButtonComponent->SetRelativeLocation(FVector(0,0,0));
	//ButtonComponent->SetWorldLocation(FVector(0,0,0));
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGamedevNosatov3dPCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGamedevNosatov3dPCharacter, Gun);
	
	//DOREPLIFETIME_CONDITION(AGamedevNosatov3dPCharacter, Gun, COND_SkipOwner);
}

float AGamedevNosatov3dPCharacter::GetHealthPercent() const
{
	return CurrentHealth/MaxHealth;
}

void AGamedevNosatov3dPCharacter::SpawnGun_Implementation()
{
	if (!GunClass) return;
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if (Gun)
	{
		GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->SetOwner(this);
		//Gun->MaxRange = WeaponRange;

		//Gun->SetOnlyOwnerSee(false);
		//Gun->bCastDynamicShadows = false;
		//Gun->CastShadow = false;
		
	}
}

bool AGamedevNosatov3dPCharacter::SpawnGun_Validate()
{
	return true;
}

void AGamedevNosatov3dPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	/*PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGamedevNosatov3dPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGamedevNosatov3dPCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGamedevNosatov3dPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGamedevNosatov3dPCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AGamedevNosatov3dPCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AGamedevNosatov3dPCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AGamedevNosatov3dPCharacter::OnResetVR);*/

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGamedevNosatov3dPCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGamedevNosatov3dPCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AGamedevNosatov3dPCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AGamedevNosatov3dPCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AGamedevNosatov3dPCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AGamedevNosatov3dPCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("PullTrigger"), EInputEvent::IE_Pressed, this, &AGamedevNosatov3dPCharacter::Shoot);
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AGamedevNosatov3dPCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &AGamedevNosatov3dPCharacter::StopCrouch);
	PlayerInputComponent->BindAction(TEXT("AnimationTest"), EInputEvent::IE_Pressed, this, &AGamedevNosatov3dPCharacter::AnimationTest);

	SpawnGun();

	/*if (ButtonClass)
	{
		UUserWidget* Button = CreateWidget<UUserWidget>(GetWorld(),ButtonClass);
		ButtonComponent->SetWidget(Button);
		
	}*/
	//ButtonComponent->SetRelativeLocationAndRotation(FVector(0,0,0),FRotator(0,180,0));
}

float AGamedevNosatov3dPCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth-=DamageToApply;
	
	return DamageToApply;
}

void AGamedevNosatov3dPCharacter::Saved()
{
	UE_LOG(LogTemp, Warning, TEXT("CHARACTER SAVED"));
}

void AGamedevNosatov3dPCharacter::Loaded()
{
	UE_LOG(LogTemp, Warning, TEXT("CHARACTER LOADED"));
}

void AGamedevNosatov3dPCharacter::Save(ABasePlayerController* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("TestVar = %d"), TestVar);
	TestVar++;
	if (GetWorld())
	{
		if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance()))
		{
			GI->Save(Player);
		}
	}
}

void AGamedevNosatov3dPCharacter::Load(ABasePlayerController* Player)
{
	if (GetWorld())
	{
		if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance()))
		{
			GI->Load(Player);
		}
	}
}


bool AGamedevNosatov3dPCharacter::IsDead() const
{
	return CurrentHealth<=0;
}

bool AGamedevNosatov3dPCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation,
	int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor) const
{
	OutSightStrength = 0.25;

	return true;
}

void AGamedevNosatov3dPCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AGamedevNosatov3dPCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AGamedevNosatov3dPCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AGamedevNosatov3dPCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AGamedevNosatov3dPCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AGamedevNosatov3dPCharacter::Jump()
{
	Super::Jump();

	/*
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseUnit::StaticClass(), FoundActors);
	for (auto Actor:FoundActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Base unit: %s"), *Actor->GetName());
		auto BaseUnit = Cast<ABaseUnit>(Actor);
		if (*BaseUnit==1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Test for int32=="));
		}
		if (Actor->IsA<UDamageInterface>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Current base unit IsA IDamageInterface"));
		}
		if (Actor->Implements<UDamageInterface>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Current base unit Implements IDamageInterface"));
		}
		if (Actor->IsA(UDamageInterface::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Current base unit IsA UDamageInterface"));
		}
		if (Actor->GetClass()->IsChildOf(UDamageInterface::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Current base unit IsChildOf UDamageInterface"));
		}
	}
	*/
}

void AGamedevNosatov3dPCharacter::StartCrouch()
{
	Super::Crouch(false);
}

void AGamedevNosatov3dPCharacter::StopCrouch()
{
	Super::UnCrouch(false);
}

bool AGamedevNosatov3dPCharacter::CanCrouch() const
{
	return Super::CanCrouch() && !GetMovementComponent()->IsFalling();
}

void AGamedevNosatov3dPCharacter::AnimationTest()
{
	if (TestMontageRef)
	{
		PlayAnimMontage(TestMontageRef, 1.f, TestMontageSectionName);
	}
	
}

//PZ #6 start
void AGamedevNosatov3dPCharacter::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("SHOOT"));
	if (Gun == nullptr) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Gun is not NULL"));
	//UE_LOG(LogTemp, Warning, TEXT("Gun is not NULL"));
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld==nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("World is not NULL"));
	ABaseGameModeBase* CurrentGameMode = Cast<ABaseGameModeBase>(UGameplayStatics::GetGameMode(CurrentWorld));

	int32 CurrentAmmoCount = 50;
	if (CurrentGameMode==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode is not NULL"));	
		//return;
	}
	else
	{
		CurrentAmmoCount = CurrentGameMode->GetAmmoCount();
	}	
	
	if (CurrentAmmoCount>0)
	{
		//Gun->PullTrigger();
		Gun->OnFire();
		CurrentAmmoCount--;
		if (CurrentGameMode) CurrentGameMode->SetAmmoCount(CurrentAmmoCount);
	}
}

float AGamedevNosatov3dPCharacter::PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	auto MeshComp = Cast<USkeletalMeshComponent>(FindComponentByClass(USkeletalMeshComponent::StaticClass()));
	UAnimInstance* AnimInstance = (MeshComp) ? MeshComp->GetAnimInstance() : nullptr;

	if (AnimMontage && AnimInstance)
	{
		float const Duration = AnimInstance->Montage_Play(AnimMontage, InPlayRate);

		if (Duration > 0.f)
		{
			//Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
			}
			return Duration;
		}
	}
	return 0.f;
	
}

//PZ #6 finish

