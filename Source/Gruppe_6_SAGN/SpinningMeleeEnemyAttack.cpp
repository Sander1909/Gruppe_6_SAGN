// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "SpinningMeleeEnemyAttack.h"


// Sets default values
ASpinningMeleeEnemyAttack::ASpinningMeleeEnemyAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpinningMeleeEnemyAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpinningMeleeEnemyAttack::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeToDestroy += DeltaTime;
	if (TimeToDestroy > 20.0f)
	{
		Destroy();
	}
	

	switch (ActorMode)
	{
	case 1:
		ActorModeTimer += DeltaTime;
		RotateActor();

		if (ActorModeTimer > 0.9f)
		{
			RotateToPlayer();
			ActorMode = 2;
		}
		break;
	case 2:
		MoveToPlayer(DeltaTime);
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("SpinningMeleeEnemyAttack error"));
		break;
	}

}

void ASpinningMeleeEnemyAttack::RotateActor()
{
	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, 7.0f, 0.0f);
	SetActorRotation(NewRotation);
}

void ASpinningMeleeEnemyAttack::RotateToPlayer()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	SetActorRotation(NewDirection.Rotation());
}

void ASpinningMeleeEnemyAttack::MoveToPlayer(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);
}

