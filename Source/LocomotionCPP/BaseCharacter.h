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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion State Values")
	ELocomotion_RotationMode PlayerRotationMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion State Values")
	ELocomotion_Gait PlayerGait;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Locomotion State Values")
	bool Aiming;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Rotation System")
	FRotator TargetRotation;

public:
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
	void UpdateCharacterMovementSettings();
	float ChooseMaxWalkSpeed();
	float ChooseMaxAcceleration();
	float ChooseBrakingDeceleration();
	float ChooseGroundFriction();
	void CalculateEssentialVariables();
	
};
