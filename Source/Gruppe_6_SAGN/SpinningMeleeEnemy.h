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

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASpinningMeleeEnemyAttack> SpinningMeleeEnemyAttack_BP;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		int Health = 4;

	void MoveForward(float DeltaTime);

	void SetEnemyRotation();

	void SpawnAttack(float DeltaTime);



private:

	bool bHitByMelee = false;
	float HitByMeleeTimer;
	float MovementValue = 10.0f;
	float SwitchModeTimer;
	float SpawnAttackTimer;
	int EnemyMode = 1;


	
	
};
