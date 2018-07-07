// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Enums/Enums.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerRole = EPlayerRole::Goalkeeper;
	PlayerTeam = EPlayerTeam::Team1;
	PlayerRotationMode = ELocomotion_RotationMode::VelocityDirection;
	PlayerGait = ELocomotion_Gait::Walking;
	Aiming = false;


	// Setting Default values for essential variables
	FRotator ActorRotation = GetActorRotation();
	LastVelocityRotation = ActorRotation;
	LookingRotation = ActorRotation;
	LastMovementInputRotation = ActorRotation;
	CharacterRotation = ActorRotation;
	TargetRotation = ActorRotation;

	WalkingSpeed = 165.0f;
	RunningSpeed = 375.0f;
	SprintingSpeed = 600.0f;
	WalkingAcceleration = 800.0f;
	RunningAcceleration = 1000.0f;
	WalkingDeceleration = RunningDeceleration = 800.0f;
	WalkingGroundFriction = 8.0f;
	RunningGroundFriction = 6.0f;

	UpdateCharacterMovementSettings();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateEssentialVariables();

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding actions
	PlayerInputComponent->BindAction("Pass", IE_Pressed, this, &ABaseCharacter::OnPass);
	PlayerInputComponent->BindAction("Kick", IE_Pressed, this, &ABaseCharacter::OnKick);
	PlayerInputComponent->BindAction("LongPass", IE_Pressed, this, &ABaseCharacter::OnLongPass);
	PlayerInputComponent->BindAction("AirPass", IE_Pressed, this, &ABaseCharacter::OnAirPass);

	// Binding axis actions
	PlayerInputComponent->BindAxis("MoveFWD/BWD", this, &ABaseCharacter::OnMoveLeftRight);
	PlayerInputComponent->BindAxis("MoveUp/Down", this, &ABaseCharacter::OnMoveUpDown);

}

void ABaseCharacter::UpdateCharacterMovementSettings()
{
	GetCharacterMovement()->MaxWalkSpeed = ChooseMaxWalkSpeed();
	GetCharacterMovement()->MaxAcceleration = ChooseMaxAcceleration();
	GetCharacterMovement()->BrakingDecelerationWalking = ChooseBrakingDeceleration();
	GetCharacterMovement()->GroundFriction = ChooseGroundFriction();
}

float ABaseCharacter::ChooseMaxWalkSpeed()
{
	if (Aiming)
	{
		switch (PlayerGait)
		{
			case ELocomotion_Gait::Walking:
			case ELocomotion_Gait::Running:
				return WalkingSpeed;
			case ELocomotion_Gait::Sprinting:
				return RunningSpeed;
			default:
				return 0.0f;
		}
	}
	else
	{
		switch (PlayerGait)
		{
		case ELocomotion_Gait::Walking:
			return WalkingSpeed;
		case ELocomotion_Gait::Running:
			return RunningSpeed;
		case ELocomotion_Gait::Sprinting:
			return SprintingSpeed;
		default:
			return 0.0f;
		}
	}
}

float ABaseCharacter::ChooseMaxAcceleration()
{
	switch (PlayerGait)
	{
		case ELocomotion_Gait::Walking:
			return WalkingAcceleration;
		case ELocomotion_Gait::Running:
		case ELocomotion_Gait::Sprinting:
			return RunningAcceleration;
		default:
			return 0.0f;
	}
}

float ABaseCharacter::ChooseBrakingDeceleration()
{
	switch (PlayerGait)
	{
		case ELocomotion_Gait::Walking:
			return WalkingDeceleration;
		case ELocomotion_Gait::Running:
		case ELocomotion_Gait::Sprinting:
			return RunningDeceleration;
		default:
			return 0.0f;
	}
}

float ABaseCharacter::ChooseGroundFriction()
{
	switch (PlayerGait)
	{
		case ELocomotion_Gait::Walking:
			return WalkingGroundFriction;
		case ELocomotion_Gait::Running:
		case ELocomotion_Gait::Sprinting:
			return RunningGroundFriction;
		default:
			return 0.0f;
	}
	
}

void ABaseCharacter::CalculateEssentialVariables()
{
	IsMoving = !GetVelocity().Equals(FVector{ 0 }, 1.0f);

	// Determine if the Character is moving, 
	// then sets the 'Last Velocity Rotation' and 'Direction' only when moving to prevent them 
	// from returning to 0 when velocity is 0.
	if (IsMoving)
	{
		LastVelocityRotation = FRotationMatrix::MakeFromX(GetVelocity()).Rotator();
		Direction = (LastVelocityRotation - CharacterRotation).Yaw;
	}
	else
	{
		// Determine if there is Movement Input, and if there is, 
		// set 'Last Movement Input Rotation' and 'Movement Input / Velocity Difference' to prevent them
		// from returning to 0 when Movement Input is 0.
		HasMovementInput = !MovementInput.Equals(FVector{ 0 }, 1.0f);
		if (HasMovementInput)
		{
			LastMovementInputRotation = FRotationMatrix::MakeFromX(MovementInput).Rotator();
			MovementInputVelocityDiff = (LastMovementInputRotation - LastVelocityRotation).Yaw;
		}
	}

	AimYawDelta = (LookingRotation - CharacterRotation).Yaw;
}

void ABaseCharacter::OnPass()
{
	UE_LOG(LogTemp, Warning, TEXT("Passing!!"));
}

void ABaseCharacter::OnKick()
{
	UE_LOG(LogTemp, Warning, TEXT("Kick!!"));
}

void ABaseCharacter::OnLongPass()
{
	UE_LOG(LogTemp, Warning, TEXT("LongPass!!"));
}

void ABaseCharacter::OnAirPass()
{
	UE_LOG(LogTemp, Warning, TEXT("AirPass!!"));
}

void ABaseCharacter::OnMoveUpDown(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("MoveUpDown!! %f"), AxisValue);
}

void ABaseCharacter::OnMoveLeftRight(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("LeftRight!! %f"), AxisValue);
}

