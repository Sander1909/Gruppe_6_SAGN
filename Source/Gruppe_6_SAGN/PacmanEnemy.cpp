// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "PacmanEnemy.h"
#include "StaticProjectile.h"


// Sets default values
APacmanEnemy::APacmanEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacmanEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APacmanEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SwitchMode += DeltaTime;

	RotateToPlayer();
	SpawnStaticProjectile(DeltaTime);

	switch (MovementMode)
	{
	case 1:
		MoveUp();

		if (SwitchMode > 1.0f)
		{
			MovementMode = Mode1[rand() % 3];
			UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);
			SwitchMode = 0.0f;
		}

		break;

	case 2:

		MoveDown();


		if (SwitchMode > 1.0f)
		{
			MovementMode = Mode2[rand() % 3];
			UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);

			SwitchMode = 0.0f;
		}
		break;

	case 3:
		MoveLeft();

		if (SwitchMode > 1.0f)
		{
			MovementMode = Mode3[rand() % 3];
			UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);

			SwitchMode = 0.0f;
		}
		break;

	case 4:
		MoveRight();

		if (SwitchMode > 1.0f)
		{
			MovementMode = Mode4[rand() % 3];
			UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);

			SwitchMode = 0.0f;
		}
		break;

	default:

		UE_LOG(LogTemp, Error, TEXT("No movement selected"));

		break;
	}

}

// Called to bind functionality to input
void APacmanEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APacmanEnemy::MoveUp()
{
	FVector MoveUp = FVector(0.0f, 1.0f, 0.0f);

	AddMovementInput(MoveUp, MovementValue);
}

void APacmanEnemy::MoveDown()
{
	FVector MoveDown = FVector(0.0f, -1.0f, 0.0f);

	AddMovementInput(MoveDown, MovementValue);
}

void APacmanEnemy::MoveLeft()
{
	FVector MoveLeft = FVector(-1.0f, 0.0f, 0.0f);

	AddMovementInput(MoveLeft, MovementValue);

}

void APacmanEnemy::MoveRight()
{
	FVector MoveRight = FVector(1.0f, 0.0f, 0.0f);

	AddMovementInput(MoveRight, MovementValue);

}

void APacmanEnemy::RotateToPlayer()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	SetActorRotation(NewDirection.Rotation());

}

void APacmanEnemy::SpawnStaticProjectile(float DeltaTime)
{
	UWorld * World;

	World = GetWorld();

	SpawnTimer += DeltaTime;

	if (SpawnTimer > 0.8f)
	{
		World->SpawnActor<AStaticProjectile>(StaticProjectile_BP, GetActorLocation(), FRotator::ZeroRotator);
		SpawnTimer = 0.0f;
	}

}