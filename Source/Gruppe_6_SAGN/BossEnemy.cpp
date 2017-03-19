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
void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	MoveForward(DeltaTime);
	RotateToPlayer();

	switch (BossMode)
	{
	case 1:
		SpawnBulletWave(DeltaTime);

		break;
	case 2:

		//Attack buffer
		NewMode += DeltaTime;

		if (NewMode > 4.0f)
		{
			BossMode = NewModeArray[rand()%2];
			NewMode = 0.0f;
		}
		break;
	case 3:
		SpawnBulletStream(DeltaTime);

		break;

	default:

		break;

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

void ABossEnemy::SpawnBulletWave(float DeltaTime)
{
	UWorld * World;

	World = GetWorld();

	FRotator CurrentRotation = GetActorRotation();

	FRotator AddYaw = FRotator(0.0f, 10.0f, 0.0f);

	FRotator NewRotation = CurrentRotation;

	FVector Location = GetActorLocation();

	BulletWaveTimer += DeltaTime;

	if (BulletWaveTimer > 1.0f)
	{
		for (int i = 0; i < 36; i++)
		{
			World->SpawnActor<ACurvingBossBullet>(CurvingBossBullet_BP, Location, NewRotation);
			NewRotation = NewRotation + AddYaw;
		}

		BulletWaveTimer = 0.0f;
		WavesSpawned++;
	}

	if (WavesSpawned > 5)
	{
		BossMode = 2;
		WavesSpawned = 0;
	}
}

void ABossEnemy::SpawnBulletStream(float DeltaTime)
{
	StopStream = StopStream + DeltaTime;
	StreamDelay = StreamDelay + DeltaTime;

	UWorld * World;

	World = GetWorld();

	FVector Location = GetActorLocation();

	if (StreamDelay > 0.15f)
	{
		AddYawToStream = AddYawToStream + 10.0f;
		AddInvertedYawToStream = AddInvertedYawToStream + 10.0f;

		FRotator NewRotationOne = FRotator(0.0, AddYawToStream, 0.0);
		FRotator NewRotationTwo = FRotator(0.0, AddInvertedYawToStream + 180, 0.0);


		World->SpawnActor<ACurvingBossBullet>(CurvingBossBullet_BP, Location, NewRotationOne);
		World->SpawnActor<ACurvingBossBullet>(CurvingBossBullet_BP, Location, -NewRotationOne);
		World->SpawnActor<ACurvingBossBullet>(CurvingBossBullet_BP, Location, NewRotationTwo);
		World->SpawnActor<ACurvingBossBullet>(CurvingBossBullet_BP, Location, -NewRotationTwo);

		StreamDelay = 0.0f;
	}

	if (StopStream > 4.0f)
	{
		BossMode = 2;
		StopStream = 0.0f;
	}

}