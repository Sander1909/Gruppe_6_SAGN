// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "Gruppe_6_SAGNGameModeBase.h"

AGruppe_6_SAGNGameModeBase::AGruppe_6_SAGNGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;

}

void AGruppe_6_SAGNGameModeBase::BeginPlay()
{

	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("This is GameMode::BeginPlay"));

}

void AGruppe_6_SAGNGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("This is GameMode::Tick"));

}
