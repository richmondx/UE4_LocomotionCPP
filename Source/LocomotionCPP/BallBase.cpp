// Fill out your copyright notice in the Description page of Project Settings.

#include "BallBase.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ABallBase::ABallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Setting Defaults
	Velocity = FVector{ 1.0f,0.0f,0.0f };

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));

	if (BallMesh)
	{
		BallMesh->SetWorldScale3D(FVector{ 0.22f });

		RootComponent = BallMesh;
	}
	
}

// Called when the game starts or when spawned
void ABallBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(Velocity);

	FRotator rot = FMath::RInterpTo(GetActorRotation(), FRotator{ 45,20,90 }, DeltaTime, 1.f);

	SetActorRotation(rot);

}

