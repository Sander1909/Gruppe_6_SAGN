// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "StandardEnemy.h"
#include "StandardEnemyProjectile.h"

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

	switch (EnemyMode)
	{
	case 1:
		MoveForward(DeltaTime);
		RotateToPlayer();
		break;
	case 2:
		Shoot(DeltaTime);
		RotateToPlayer();
		break;
	}
}

void AStandardEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStandardEnemy::MoveForward(float DeltaTime)
{
	FVector ForwardVector = GetActorForwardVector() * Speed * DeltaTime;

	AddMovementInput(ForwardVector, MovementValue);
}

void AStandardEnemy::RotateToPlayer()
{
	
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	SetActorRotation(NewDirection.Rotation());

	if (NewDirection.Size() <= ShootRange)
	{
		EnemyMode = 2;
	}

}

void AStandardEnemy::Shoot(float DeltaTime)
{
	UWorld * World;

	World = GetWorld();

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * SpawnBuffer;

	ShootTimer += DeltaTime;

	if (ShootTimer >= 2.5f)
	{
		World->SpawnActor<AStandardEnemyProjectile>(StandardEnemyProjectile_BP, SpawnLocation, GetActorRotation());
		ShootTimer = 0.0f;
	}


	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	if (NewDirection.Size() > ShootRange)
	{
		EnemyMode = 1;
	}

}