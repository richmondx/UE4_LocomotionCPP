// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class LOCOMOTIONCPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Info")
	EPlayerTeam PlayerTeam;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Info")
	EPlayerRole PlayerRole;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	bool ShouldSprint;

	//========================================================
	//============ Essential Variables ==============
	//========================================================
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	FVector MovementInput;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	float AimYawDelta;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	float AimYawRate;	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	float MovementInputVelocityDiff;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	float TargetAndCharacterRotationDiff;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	FRotator CharacterRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	FRotator LookingRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	FRotator LastVelocityRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	FRotator LastMovementInputRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	bool IsMoving;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Essential Variables")
	bool HasMovementInput;

public:
	//========================================================
	//============ Locomotion State Values ==============
	//========================================================
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion State Values")
	ELocomotion_RotationMode PlayerRotationMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion State Values")
	ELocomotion_Gait PlayerGait;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion State Values")
	bool Aiming;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Rotation System")
	ELocomotion_CardinalDirection PlayerCardinalDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Rotation System")
	FRotator TargetRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Rotation System")
	float RotationOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Rotation System")
	float RotationRateMultiplier;


public:
	//========================================================
	//============ Locomotion Movement Settings ==============
	//========================================================
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float WalkingSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float RunningSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float SprintingSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float WalkingAcceleration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float RunningAcceleration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float WalkingDeceleration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float RunningDeceleration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float WalkingGroundFriction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion Movement Settings")
	float RunningGroundFriction;
public:
	
private:
	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	void UpdateCharacterMovementSettings();

	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	void CustomAcceleration();

	void SprintCheck();

	float ChooseMaxWalkSpeed();
	float ChooseMaxAcceleration();
	float ChooseBrakingDeceleration();
	float ChooseGroundFriction();
	void CalculateEssentialVariables();
	void ManageCharacterRotation();

	//========================================================
	//============ Character Rotation Functions ==============
	//========================================================
	UFUNCTION(BlueprintCallable, Category = "Character Rotation")
	void SetCharacterRotation(FRotator TargetRot, bool InterpRotation, float InterpSpeed);

	UFUNCTION(BlueprintCallable, Category = "Character Rotation")
	void AddCharacterRotation(FRotator AddAmount);

	UFUNCTION(BlueprintCallable, Category = "Character Rotation")
	FRotator LookingDirectionWithOffset(float OffsetInterpSpeed,float NE_Angle, float NW_Angle, float SE_Angle, float SW_Angle, float Buffer);

	UFUNCTION(BlueprintCallable, Category = "Character Rotation")
	float CalculateRotationRate(float SlowSpeed,float SlowSpeedRate,float FastSpeed, float FastSpeedRate);

	UFUNCTION(BlueprintCallable, Category = "Character Rotation")
	void LimitRotation(float AimYawLimit, float InterpSpeed);
public:
	//===================================================================================
	//============ BlueprintImplementable Functions (Custom Events in BPs) ==============
	//===================================================================================
	UFUNCTION(BlueprintNativeEvent, Category = "OnChanged")
	void OnRotationModeChanged();
	virtual void OnRotationModeChanged_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "OnChanged")
	void SetGaitEvent(ELocomotion_Gait Gait);
	virtual void SetGaitEvent_Implementation(ELocomotion_Gait Gait);
	
	UFUNCTION(BlueprintNativeEvent, Category = "OnChanged")
	void SetRotationModeEvent(ELocomotion_RotationMode RotMode);
	virtual void SetRotationModeEvent_Implementation(ELocomotion_RotationMode RotMode);

	UFUNCTION(BlueprintNativeEvent, Category = "OnChanged")
	void SetAimingModeEvent(bool NewAiming);
	virtual void SetAimingModeEvent_Implementation(bool NewAiming);

	UFUNCTION(BlueprintNativeEvent, Category = "OnChanged")
	void SetWalkingSpeedEvent(float NewWalkingSpeed);
	virtual void SetWalkingSpeedEvent_Implementation(float NewWalkingSpeed);

	UFUNCTION(BlueprintNativeEvent, Category = "OnChanged")
	void SetRunningSpeedEvent(float NewRunningSpeed);
	virtual void SetRunningSpeedEvent_Implementation(float NewRunningSpeed);

	UFUNCTION(BlueprintNativeEvent, Category = "OnChanged")
	void SetSprintingSpeedEvent(float NewSprintingSpeed);
	virtual void SetSprintingSpeedEvent_Implementation(float NewSprintingSpeed);
protected:
	// input component functions
	void OnPass();
	void OnKick();
	void OnLongPass();
	void OnAirPass();
	void OnSprint();
	void OnChangePlayer();
	void OnMoveUpDown(float AxisValue);
	void OnMoveLeftRight(float AxisValue);

private:
	//========================================================
	//============ Calculational Functions ===================
	//========================================================
	bool CardinalDirectionAngles(float Value, float Min, float Max, float Buffer, ELocomotion_CardinalDirection CardinalDirection);
	
};
