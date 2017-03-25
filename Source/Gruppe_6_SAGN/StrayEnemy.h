// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "StrayEnemy.generated.h"

UCLASS()
class GRUPPE_6_SAGN_API AStrayEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStrayEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RotateToPlayer();

	void MoveForward(float DeltaTime);

	void SpawnProjectile();

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AStandardEnemyProjectile> StandardEnemyProjectile_BP;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

private:

	bool bHitByMelee = false;

	float HitByMeleeTimer;

	float MovementValue = 600.0f;

	float ShootTimer;

	
	
};
