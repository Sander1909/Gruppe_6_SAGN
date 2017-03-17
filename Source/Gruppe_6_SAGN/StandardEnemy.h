// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "StandardEnemy.generated.h"

UCLASS()
class GRUPPE_6_SAGN_API AStandardEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStandardEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float DeltaTime);
	void RotateToPlayer();

	void Shoot(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AStandardEnemyProjectile> StandardEnemyProjectile_BP;

private:
	
	float Speed = 30.0f;

	float MovementValue = 100.0f;

	float SpawnBuffer = 30.0f;

	float ShootRange = 700.0f;

	float ShootTimer;

	int Health = 5;

	int EnemyMode = 1;

	//EnemyMode 1: Chase and rotate towards player
	//EnemyMode 2: Stand still and shoot towards player
};
