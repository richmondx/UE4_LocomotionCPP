// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Enums/Enums.h"
#include "UObject/Object.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LocomotionStructs.generated.h"


// todo

USTRUCT(BlueprintType)
struct FLocomotionPivotParams
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Pivot Params")
	float PivotDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Pivot Params")
	float InterruptedStartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Pivot Params")
	float CompletedStartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Pivot Params")
	ELocomotion_MovementDirection CompletedMovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Pivot Params")
	ELocomotion_MovementDirection InterruptedMovementDirection;

	FLocomotionPivotParams()
	{
		PivotDirection = 0.0f;
		InterruptedStartTime = 0.0f;
		CompletedStartTime = 0.0f;
		CompletedMovementDirection = ELocomotion_MovementDirection::Forwards;
		InterruptedMovementDirection = ELocomotion_MovementDirection::Forwards;
	}
};