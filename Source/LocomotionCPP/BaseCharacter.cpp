// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "Enums/Enums.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerRole = EPlayerRole::Goalkeeper;
	PlayerTeam = EPlayerTeam::Team1;
	PlayerCardinalDirection = ELocomotion_CardinalDirection::North;
	PlayerRotationMode = ELocomotion_RotationMode::VelocityDirection;
	PlayerGait = ELocomotion_Gait::Walking;
	Aiming = false;
	ShouldSprint = false;


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


	OnRotationModeChanged();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateEssentialVariables();
	CustomAcceleration();


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
	PlayerInputComponent->BindAction("Sprint", IE_Repeat, this, &ABaseCharacter::OnSprint);
	PlayerInputComponent->BindAction("ChangePlayer", IE_Pressed, this, &ABaseCharacter::OnChangePlayer);

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

void ABaseCharacter::CustomAcceleration()
{
	GetCharacterMovement()->MaxAcceleration = RunningAcceleration * FMath::GetMappedRangeValueClamped(FVector2D{ 45.0f, 130.0f }, FVector2D{ 1.0f, 0.2f }, FMath::Abs(MovementInputVelocityDiff));
	GetCharacterMovement()->GroundFriction = RunningGroundFriction * FMath::GetMappedRangeValueClamped(FVector2D{ 45.0f, 130.0f }, FVector2D{ 1.0f, 0.4f }, FMath::Abs(MovementInputVelocityDiff));
}

void ABaseCharacter::SprintCheck()
{
	// todo
	if (ShouldSprint)
	{

	}
	else
	{

	}
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

void ABaseCharacter::ManageCharacterRotation()
{
	if (IsMoving)
	{
		auto TargetRot = LookingDirectionWithOffset(5.0f, 60.0f, -60.0f, 120.0f, -120.0f, 5.0f);

		switch (PlayerRotationMode)
		{
			case ELocomotion_RotationMode::LookingDirection:
			{
				if (Aiming)
				{
					auto RotationRate = CalculateRotationRate(165.f, 15.f, 375.f, 15.f);
					SetCharacterRotation(TargetRot, true, RotationRate);
				}
				else
				{
					auto RotationRate = CalculateRotationRate(165.f, 10.f, 375.f, 15.f);
					SetCharacterRotation(TargetRot, true, RotationRate);
				}
				break;
			}
			case ELocomotion_RotationMode::VelocityDirection:
			{
				auto RotationRate = CalculateRotationRate(165.f, 5.f, 375.f, 10.f);
				SetCharacterRotation(FRotator{ 0.0f, 0.0f, LastVelocityRotation.Yaw }, true, RotationRate);
				break;
			}
			default:
				break;
		}
	}
	else
	{
		if (!IsPlayingRootMotion() && PlayerRotationMode == ELocomotion_RotationMode::LookingDirection && Aiming)
		{
			LimitRotation(90.0f, 15.0f);	
		}
	}
}

FRotator ABaseCharacter::LookingDirectionWithOffset(float OffsetInterpSpeed, float NE_Angle, float NW_Angle, float SE_Angle, float SW_Angle, float Buffer)
{
	FRotator TargetRotation{0.0f, 0.0f, 0.0f};
	float RotDeltaYaw = (HasMovementInput) ? (LastMovementInputRotation - LookingRotation).Yaw : (LastVelocityRotation - LookingRotation).Yaw;

	if (CardinalDirectionAngles(RotDeltaYaw, NW_Angle, NE_Angle, Buffer, ELocomotion_CardinalDirection::North))
	{
		PlayerCardinalDirection = ELocomotion_CardinalDirection::North;
	}
	else if (CardinalDirectionAngles(RotDeltaYaw, NE_Angle, SE_Angle, Buffer, ELocomotion_CardinalDirection::East))
	{
		PlayerCardinalDirection = ELocomotion_CardinalDirection::East;
	}
	else if (CardinalDirectionAngles(RotDeltaYaw, SW_Angle, NW_Angle, Buffer, ELocomotion_CardinalDirection::West))
	{
		PlayerCardinalDirection = ELocomotion_CardinalDirection::West;
	}
	else
	{
		PlayerCardinalDirection = ELocomotion_CardinalDirection::South;
	}

	// Based On Direction Calculation RotationOffset
	float DirectionTargetOffset;
	switch (PlayerCardinalDirection)
	{
		case ELocomotion_CardinalDirection::North:
			DirectionTargetOffset = RotDeltaYaw;
			break;
		case ELocomotion_CardinalDirection::East:
			DirectionTargetOffset = RotDeltaYaw - 90.0f;
			break;
		case ELocomotion_CardinalDirection::West:
			DirectionTargetOffset = RotDeltaYaw + 90.0f;
			break;
		case ELocomotion_CardinalDirection::South:
			DirectionTargetOffset = (RotDeltaYaw > 0.0f) ? RotDeltaYaw - 180.0f : RotDeltaYaw + 180.0f;
			break;
	}

	auto World = GetWorld();
	if (World)
	{
		RotationOffset = FMath::FInterpTo(RotationOffset, DirectionTargetOffset, GetWorld()->GetDeltaSeconds(), OffsetInterpSpeed);
	}

	TargetRotation.Yaw = LookingRotation.Yaw + RotationOffset;
	
	return TargetRotation;
}

void ABaseCharacter::SetCharacterRotation(FRotator TargetRot, bool InterpRotation, float InterpSpeed)
{
	TargetRotation = TargetRot;
	TargetAndCharacterRotationDiff = (TargetRotation - CharacterRotation).Yaw;
	if (InterpRotation)
	{
		if (InterpSpeed != 0.0)
		{
			auto World = GetWorld();
			if (World)
			{				
				CharacterRotation = FMath::RInterpTo(CharacterRotation, TargetRotation, UGameplayStatics::GetWorldDeltaSeconds(World), InterpSpeed);
			}
		}
	}
	else
	{
		CharacterRotation = TargetRotation;
	}

	SetActorRotation(CharacterRotation);
}

void ABaseCharacter::AddCharacterRotation(FRotator AddAmount)
{
	TargetRotation = TargetRotation - AddAmount.GetInverse();
	TargetAndCharacterRotationDiff = (TargetRotation - CharacterRotation).Yaw;
	CharacterRotation = CharacterRotation - AddAmount.GetInverse();
	SetActorRotation(CharacterRotation);
}

float ABaseCharacter::CalculateRotationRate(float SlowSpeed, float SlowSpeedRate, float FastSpeed, float FastSpeedRate)
{
	FVector Velocity = FVector{ GetVelocity().X, GetVelocity().Y, 0.0f };
	float VelocitySize = Velocity.Size();
	float result;

	if (VelocitySize > SlowSpeed)
	{
		result = FMath::GetMappedRangeValueUnclamped(FVector2D{ SlowSpeed, FastSpeed }, FVector2D{ SlowSpeedRate, FastSpeedRate }, VelocitySize);
	}
	else
	{
		result = FMath::GetMappedRangeValueClamped(FVector2D{ 0.0f,SlowSpeed }, FVector2D{ 0.0f,SlowSpeedRate }, VelocitySize);
	}


	if (RotationRateMultiplier == 1.0f)
	{
		result *= RotationRateMultiplier;
	}
	else
	{
		auto World = GetWorld();
		if (World)
		{
			RotationRateMultiplier = FMath::Clamp(RotationRateMultiplier + World->GetDeltaSeconds(), 0.0f, 1.0f);
		}
	}

	
	return FMath::Clamp(result, 0.1f, 15.0f);
}

void ABaseCharacter::LimitRotation(float AimYawLimit, float InterpSpeed)
{
	if (FMath::Abs(AimYawDelta) > AimYawLimit)
	{
		FRotator TargetRot;
		TargetRot.Yaw = AimYawDelta > 0.0f ? LookingRotation.Yaw + AimYawLimit : LookingRotation.Yaw - AimYawLimit;
		SetCharacterRotation(TargetRot, true, InterpSpeed);
	}
}

void ABaseCharacter::OnRotationModeChanged_Implementation()
{
	if (IsMoving)
	{
		RotationRateMultiplier = 0.0f;
	}
}

void ABaseCharacter::SetGaitEvent_Implementation(ELocomotion_Gait Gait)
{
	if (DoIfDifferent(PlayerGait, Gait))
	{
		PlayerGait = Gait;
		UpdateCharacterMovementSettings();
	}
}

void ABaseCharacter::SetRotationModeEvent_Implementation(ELocomotion_RotationMode RotMode)
{
	if (DoIfDifferent(PlayerRotationMode, RotMode))
	{
		PlayerRotationMode = RotMode;
		OnRotationModeChanged();
	}
}

void ABaseCharacter::SetAimingModeEvent_Implementation(bool NewAiming)
{
	if (DoIfDifferent(Aiming, NewAiming))
	{
		Aiming = NewAiming;
		UpdateCharacterMovementSettings();
	}
}

void ABaseCharacter::SetWalkingSpeedEvent_Implementation(float NewWalkingSpeed)
{
	if (DoIfDifferent(WalkingSpeed, NewWalkingSpeed))
	{
		WalkingSpeed = NewWalkingSpeed;
		UpdateCharacterMovementSettings();
	}
}

void ABaseCharacter::SetRunningSpeedEvent_Implementation(float NewRunningSpeed)
{
	if (DoIfDifferent(RunningSpeed, NewRunningSpeed))
	{
		RunningSpeed = NewRunningSpeed;
		UpdateCharacterMovementSettings();
	}
}

void ABaseCharacter::SetSprintingSpeedEvent_Implementation(float NewSprintingSpeed)
{
	if (DoIfDifferent(SprintingSpeed, NewSprintingSpeed))
	{
		SprintingSpeed = NewSprintingSpeed;
		UpdateCharacterMovementSettings();
	}
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

void ABaseCharacter::OnSprint()
{
	UE_LOG(LogTemp, Warning, TEXT("On Sprint !!"));
}

void ABaseCharacter::OnChangePlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("On Player Change!!"));
}

void ABaseCharacter::OnMoveUpDown(float AxisValue)
{
	AddMovementInput(FVector{ 0.0f, -1.0f, 0.0f }, AxisValue);
}

void ABaseCharacter::OnMoveLeftRight(float AxisValue)
{
	AddMovementInput(FVector{ 1.0f, 0.0f, 0.0f }, AxisValue);
}

bool ABaseCharacter::CardinalDirectionAngles(float Value, float Min, float Max, float Buffer, ELocomotion_CardinalDirection CardinalDirection)
{
	if (PlayerCardinalDirection == CardinalDirection)
	{
		return UKismetMathLibrary::InRange_FloatFloat(Value, Min - Buffer, Max + Buffer);
	}
	else
	{
		return UKismetMathLibrary::InRange_FloatFloat(Value, Min + Buffer, Max - Buffer);
	}
}

