// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "StrayEnemy.h"
#include "StandardEnemyProjectile.h"


// Sets default values
AStrayEnemy::AStrayEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrayEnemy::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<UCapsuleComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AStrayEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StrayEnemy no collision box"));

	}
	
}

// Called every frame
void AStrayEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	ShootTimer += DeltaTime;

	MoveForward(DeltaTime);

	if (ShootTimer > 3.5f)
	{
		SpawnProjectile();

		RotateToPlayer();

		ShootTimer = 0.0;
	}

}

// Called to bind functionality to input
void AStrayEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStrayEnemy::RotateToPlayer()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	SetActorRotation(NewDirection.Rotation());
}

void AStrayEnemy::MoveForward(float DeltaTime)
{
	FVector ForwardVector = GetActorForwardVector() * DeltaTime;

	AddMovementInput(ForwardVector, MovementValue);
}

void AStrayEnemy::SpawnProjectile()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator ProjectileRotation = GetActorRotation();
	FRotator AddYaw = FRotator(0.0f, 30.0f, 0.0f);

	UWorld * World;

	World = GetWorld();

	for (int i = 0; i < 12; i++)
	{
		World->SpawnActor<AStandardEnemyProjectile>(StandardEnemyProjectile_BP, SpawnLocation, ProjectileRotation);
		ProjectileRotation = ProjectileRotation + AddYaw;
	}

}

void AStrayEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	/*if (OtherActor->IsA(AStandardEnemyProjectile::StaticClass()))
	{

	}*/
}
