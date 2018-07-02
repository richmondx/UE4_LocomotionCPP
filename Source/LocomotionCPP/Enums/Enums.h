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
