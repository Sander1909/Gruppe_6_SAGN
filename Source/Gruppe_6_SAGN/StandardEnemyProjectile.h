// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StandardEnemyProjectile.generated.h"

UCLASS()
class GRUPPE_6_SAGN_API AStandardEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStandardEnemyProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetProjectileLocation(float DeltaTime);

	UPROPERTY(EditAnywhere)
		UShapeComponent * CollisionBox;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
			UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult &SweepResult);


private:

	float Speed = 800.0f;
	
	float TimeToDestroy;
};
