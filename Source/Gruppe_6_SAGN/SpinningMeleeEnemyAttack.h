// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpinningMeleeEnemyAttack.generated.h"

UCLASS()
class GRUPPE_6_SAGN_API ASpinningMeleeEnemyAttack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpinningMeleeEnemyAttack();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void RotateActor();

	void RotateToPlayer();

	void MoveToPlayer(float DeltaTime);

private:

	int ActorMode = 1;
	float ActorModeTimer;
	float TimeToDestroy;
	float Speed = 600.0f;

	FVector NewLocation;
};