// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamedevNosatov3dPCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
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
}

void AGamedevNosatov3dPCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

//////////////////////////////////////////////////////////////////////////
// Input

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

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}


bool AGamedevNosatov3dPCharacter::IsDead() const
{
	return false;
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
}

//PZ #6 start
void AGamedevNosatov3dPCharacter::Shoot()
{	
	if (Gun == nullptr) return;
	UWorld* CurrentWorld = GetWorld();
	if (CurrentWorld==nullptr) return;
	ABaseGameModeBase* CurrentGameMode = Cast<ABaseGameModeBase>(UGameplayStatics::GetGameMode(CurrentWorld));
	if (CurrentGameMode==nullptr) return;
	
	int32 CurrentAmmoCount = CurrentGameMode->GetAmmoCount();
	if (CurrentAmmoCount>0)
	{
		Gun->PullTrigger();
		CurrentAmmoCount--;
		CurrentGameMode->SetAmmoCount(CurrentAmmoCount);
	}
}
//PZ #6 finish