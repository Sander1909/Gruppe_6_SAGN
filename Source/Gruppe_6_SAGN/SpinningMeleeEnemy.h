// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SpinningMeleeEnemy.generated.h"

UCLASS()
class GRUPPE_6_SAGN_API ASpinningMeleeEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpinningMeleeEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

	void MoveForward(float DeltaTime);

	void SetEnemyRotation();

	void DashAttack(float DeltaTime);


private:

	bool bHitByMelee = false;

	float HitByMeleeTimer;

	float MovementValue = 5.0f;

	float EnemySwitchMode;

	float DashRotationTimer;

	int Health = 2;

	int EnemyMode = 1;


	
	
};
