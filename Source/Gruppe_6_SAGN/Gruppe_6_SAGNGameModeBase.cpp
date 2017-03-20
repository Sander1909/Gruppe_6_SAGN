// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "Gruppe_6_SAGNGameModeBase.h"
#include "StandardEnemy.h"
#include "PacmanEnemy.h"
#include "RandomEnemy.h"
#include "StrayEnemy.h"
#include "BossEnemy.h"

AGruppe_6_SAGNGameModeBase::AGruppe_6_SAGNGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;

}

void AGruppe_6_SAGNGameModeBase::BeginPlay()
{

	Super::BeginPlay();

	SpawnStandardEnemy();


}

void AGruppe_6_SAGNGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += 1;

	switch (WaveNumber)
	{
	case 1:

		if (Timer % 180 == 0)
		{
			//SpawnStandardEnemy();
		}
		if (Timer % 300 == 0)
		{
			//SpawnStrayEnemy();
		}
		if (Timer % 400 == 0)
		{
			SpawnPacmanEnemy();
		}
		if (Timer % 2000 == 0)
		{
			SpawnBossEnemy();
		}
		break;
	}


}

void AGruppe_6_SAGNGameModeBase::SpawnStandardEnemy()
{
	World = GetWorld();

	FVector Location = FVector(1000.f, -1000.0f, 0.0f);

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - Location;


	World->SpawnActor<AStandardEnemy>(StandardEnemy_BP, Location, NewDirection.Rotation());
}

void AGruppe_6_SAGNGameModeBase::SpawnPacmanEnemy()
{
	World = GetWorld();

	FVector Location = FVector(-1000.0f, 0.0f, 0.0f);

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - Location;


	World->SpawnActor<APacmanEnemy>(PacmanEnemy_BP, Location, NewDirection.Rotation());
}

void AGruppe_6_SAGNGameModeBase::SpawnRandomEnemy()
{
	World = GetWorld();

	FVector Location = FVector(-1000.f, -1000.0f, 0.0f);

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - Location;


	World->SpawnActor<ARandomEnemy>(RandomEnemy_BP, Location, NewDirection.Rotation());
}

void AGruppe_6_SAGNGameModeBase::SpawnStrayEnemy()
{
	World = GetWorld();

	FVector Location = FVector(1000.f, 1000.0f, 0.0f);

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - Location;

	World->SpawnActor<AStrayEnemy>(StrayEnemy_BP, Location, NewDirection.Rotation());
}

void AGruppe_6_SAGNGameModeBase::SpawnBossEnemy()
{
	World = GetWorld();

	FVector Location = FVector(0.0f, 0.0f, 2000.0f);

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - Location;


	World->SpawnActor<ABossEnemy>(BossEnemy_BP, Location, NewDirection.Rotation());
}
