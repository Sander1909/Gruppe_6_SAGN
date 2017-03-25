// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "StandardEnemy.h"
#include "StandardEnemyProjectile.h"
#include "PlayerProjectile.h"
#include "PlayerMeleeAttack.h"

AStandardEnemy::AStandardEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AStandardEnemy::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<UCapsuleComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStandardEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StandardEnemy no collision box"));

	}
}

void AStandardEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!bHitByMelee)
	{
		switch (EnemyMode)
		{
		case 1:
			MoveForward(DeltaTime);
			RotateToPlayer();
			break;
		case 2:
			SpawnProjectile(DeltaTime);
			RotateToPlayer();
			break;
		}
	}
	else if (bHitByMelee)
	{
		HitByMeleeTimer += DeltaTime;

		if (HitByMeleeTimer < 0.5f)
		{
			AddMovementInput(GetActorLocation() - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), MovementValue);
		}
		else if (HitByMeleeTimer >= 0.5f)
		{
			if (HitByMeleeTimer > 1.5f)
			{
				HitByMeleeTimer = 0.0f;
				bHitByMelee = false;
			}
		}
	}

}

void AStandardEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStandardEnemy::MoveForward(float DeltaTime)
{
	FVector ForwardVector = GetActorForwardVector() * DeltaTime;

	AddMovementInput(ForwardVector, MovementValue);
}

void AStandardEnemy::RotateToPlayer()
{
	
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	SetActorRotation(NewDirection.Rotation());

	if (NewDirection.Size() <= ShootRange)
	{
		EnemyMode = 2;
	}

}

void AStandardEnemy::SpawnProjectile(float DeltaTime)
{
	UWorld * World;

	World = GetWorld();

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * SpawnBuffer;

	ShootTimer += DeltaTime;

	if (ShootTimer >= 2.5f)
	{
		World->SpawnActor<AStandardEnemyProjectile>(StandardEnemyProjectile_BP, SpawnLocation, GetActorRotation());
		ShootTimer = 0.0f;
	}


	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	if (NewDirection.Size() > ShootRange)
	{
		EnemyMode = 1;
	}

}

void AStandardEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(APlayerProjectile::StaticClass()))
	{
		Health--;
		if (Health < 1)
		{
			Destroy();
		}

		OtherActor->Destroy();

		UE_LOG(LogTemp, Warning, TEXT("StandardEnemy health is: %i"), Health);
	}
	else if (OtherActor->IsA(APlayerMeleeAttack::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Standard Enemy was hit by PlayerMeleeAttack"));
		bHitByMelee = true;
		HitByMeleeTimer = 0.0f;

	}
}