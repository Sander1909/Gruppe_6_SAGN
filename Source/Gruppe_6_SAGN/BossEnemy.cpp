// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "BossEnemy.h"
#include "PlayerProjectile.h"
#include "CurvingBossBullet.h"


// Sets default values
ABossEnemy::ABossEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox = this->FindComponentByClass<UCapsuleComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BossEnemy no collision box"));
	}
}

// Called every frame
void ABossEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	BulletWaveTimer += DeltaTime;

	MoveForward(DeltaTime);
	RotateToPlayer();

	if (BulletWaveTimer > 1.0f)
	{
		SpawnBulletWave();
		BulletWaveTimer = 0.0f;
	}
}

// Called to bind functionality to input
void ABossEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABossEnemy::MoveForward(float DeltaTime)
{
	FVector ForwardVector = GetActorForwardVector() * DeltaTime;

	AddMovementInput(ForwardVector, MovementValue);

}

void ABossEnemy::RotateToPlayer()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector NewDirection = PlayerLocation - GetActorLocation();

	NewDirection.Z = 0.0f;

	SetActorRotation(NewDirection.Rotation());
}

void ABossEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(APlayerProjectile::StaticClass()))
	{
		Health--;
		if (Health < 0)
		{
			Destroy();
		}
		OtherActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Boss health: %i"), Health);
	}
}

void ABossEnemy::SpawnBulletWave()
{
	UWorld * World;

	World = GetWorld();

	FRotator CurrentRotation = GetActorRotation();

	FRotator AddYaw = FRotator(0.0f, 10.0f, 0.0f);

	FRotator NewRotation = CurrentRotation;

	FVector Location = GetActorLocation();

	for (int i = 0; i < 36; i++)
	{
		World->SpawnActor<ACurvingBossBullet>(CurvingBossBullet_BP, Location, NewRotation);
		NewRotation = NewRotation + AddYaw;
	}

}