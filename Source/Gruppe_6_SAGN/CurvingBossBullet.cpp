// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "CurvingBossBullet.h"


// Sets default values
ACurvingBossBullet::ACurvingBossBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACurvingBossBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACurvingBossBullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeToDestroy += DeltaTime;

	MoveForward(DeltaTime);
	CurveLeft();

	if (TimeToDestroy > 8.0f)
	{
		Destroy();
	}

}

void ACurvingBossBullet::MoveForward(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	SetActorLocation(NewLocation);
}

void ACurvingBossBullet::CurveLeft()
{
	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, 0.5f, 0.0f);

	SetActorRotation(NewRotation);
}