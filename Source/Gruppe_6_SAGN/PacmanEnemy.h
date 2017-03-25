// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PacmanEnemy.generated.h"

UCLASS()
class GRUPPE_6_SAGN_API APacmanEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacmanEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void RotateToPlayer();
	void SpawnStaticProjectile(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class AStaticProjectile> StaticProjectile_BP;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox = nullptr;

private:

	bool bHitByMelee = false;

	float HitByMeleeTimer;

	float MovementValue = 200.0f;

	int MovementMode = rand() %4+1;

	float SwitchMode;

	float SpawnTimer;
	
	int Mode1[2] = {3,4};
	int Mode2[2] = {3,4};
	int Mode3[2] = {1,2};
	int Mode4[2] = {1,2};
	
};
