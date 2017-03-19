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

	void SpawnProjectile(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AStandardEnemyProjectile> StandardEnemyProjectile_BP;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);
	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

private:
	
	float MovementValue = 1000.0f;

	float SpawnBuffer = 30.0f;

	float ShootRange = 700.0f;

	float ShootTimer;

	int EnemyMode = 1;

	int Health = 4;

	//EnemyMode 1: Chase and rotate towards player
	//EnemyMode 2: Stand still and shoot towards player
};
