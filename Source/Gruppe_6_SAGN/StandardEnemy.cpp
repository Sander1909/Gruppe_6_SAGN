// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "StandardEnemy.h"

AStandardEnemy::AStandardEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AStandardEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AStandardEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector ForwardVector = GetActorForwardVector() * Speed * DeltaTime;

	AddMovementInput(ForwardVector, MovementValue);
}

void AStandardEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

