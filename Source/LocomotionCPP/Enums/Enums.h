// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerTeam : uint8
{
	Team1,
	Team2,
};

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Defender,
	MidDefender,
	Forward,
	Goalkeeper
};