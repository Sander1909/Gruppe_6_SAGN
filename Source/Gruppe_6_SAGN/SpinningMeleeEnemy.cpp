// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "SpinningMeleeEnemy.h"


// Sets default values
ASpinningMeleeEnemy::ASpinningMeleeEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpinningMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpinningMeleeEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UE_LOG(LogTemp, Warning, TEXT("Move is %f"), MovementValue);

	EnemySwitchMode += DeltaTime;

	switch (EnemyMode)
	{
	case 1:

	MoveForward(DeltaTime);
	SetEnemyRotation();

	if (EnemySwitchMode > 5.0f)
	{
		EnemyMode = 2;
		EnemySwitchMode = 0.0f;
	}

		break;

	case 2:
		DashAttack(DeltaTime);

		if (EnemySwitchMode > 6.0f)
		{
			EnemyMode = 1;
			EnemySwitchMode = 0.0f;
			MovementValue = 5.0f;
		}

		break;

	default:
		break;
	}

}

// Called to bind functionality to input
void ASpinningMeleeEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpinningMeleeEnemy::MoveForward(float DeltaTime)
{
	FVector ForwardVector = GetActorForwardVector() * DeltaTime;

	AddMovementInput(ForwardVector, MovementValue);
}

void ASpinningMeleeEnemy::SetEnemyRotation()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	NewDirection.Z = 0.0f;

	SetActorRotation(NewDirection.Rotation());
}

void ASpinningMeleeEnemy::DashAttack(float DeltaTime)
{
	DashRotationTimer += DeltaTime;

	MovementValue = 700.0f;

	MoveForward(DeltaTime);

	if (DashRotationTimer > 1.5f)
	{
		SetEnemyRotation();
		DashRotationTimer = 0.0f;
	}

}
