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

}

void AGruppe_6_SAGNGameModeBase::SpawnRandomEnemy()
{

}

void AGruppe_6_SAGNGameModeBase::SpawnStrayEnemy()
{

}

void AGruppe_6_SAGNGameModeBase::SpawnBossEnemy()
{

}
