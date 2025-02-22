// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EPlayerTeam : uint8
{
	Team1 UMETA(DisplayName = "Team1"),
	Team2 UMETA(DisplayName = "Team2"),
};

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Defender UMETA(DisplayName = "Defender"),
	MidDefender UMETA(DisplayName = "MidDefender"),
	Forward UMETA(DisplayName = "Forward"),
	Goalkeeper UMETA(DisplayName = "Goalkeeper")
};

UENUM(BlueprintType)
enum class ELocomotion_Gait : uint8
{
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Running"),
	Sprinting UMETA(DisplayName = "Sprinting")	
};

UENUM(BlueprintType)
enum class ELocomotion_RotationMode : uint8
{
	LookingDirection UMETA(DisplayName = "LookingDirection"),
	VelocityDirection UMETA(DisplayName = "VelocityDirection"),
};

UENUM(BlueprintType)
enum class ELocomotion_CardinalDirection : uint8
{
	North UMETA(DisplayName = "North"),
	East UMETA(DisplayName = "East"),
	West UMETA(DisplayName = "West"),
	South UMETA(DisplayName = "South"),
};

UENUM(BlueprintType)
enum class ELocomotion_MovementDirection : uint8
{
	Forwards UMETA(DisplayName = "Forwards"),
	Backwards UMETA(DisplayName = "Backwards"),
};

UENUM(BlueprintType)
enum class ELocomotion_State : uint8
{
	None UMETA(DisplayName = "None"),
	NotMoving UMETA(DisplayName = "NotMoving"),
	Moving UMETA(DisplayName = "Moving"),
	Pivot UMETA(DisplayName = "Pivot"),
	Stopping UMETA(DisplayName = "Stopping"),
};


template<typename T>
bool DoIfDifferent(T A, T B)
{
	return A != B;
}