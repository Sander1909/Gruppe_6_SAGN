// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "PacmanEnemy.h"
#include "StaticProjectile.h"
#include "PlayerMeleeAttack.h"


// Sets default values
APacmanEnemy::APacmanEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacmanEnemy::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<UCapsuleComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APacmanEnemy::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PacmanEnemy no collision box"));

	}

}

// Called every frame
void APacmanEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SwitchMode += DeltaTime;

	RotateToPlayer();
	SpawnStaticProjectile(DeltaTime);

	//Default mode guard.
	if (!bHitByMelee)
	{
		switch (MovementMode)
		{
		case 1:
			MoveUp();

			if (SwitchMode > 1.0f)
			{
				if (GetActorLocation().X > 2000)
				{
					MovementMode = 2;
					SwitchMode = 0.0f;
					UE_LOG(LogTemp, Error, TEXT("Detected wall"));

				}
				else
				{
					MovementMode = Mode1[rand() % 2];
					UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);
					SwitchMode = 0.0f;
				}

			}

			break;

		case 2:

			MoveDown();



			if (SwitchMode > 1.0f)
			{
				if (SwitchMode > 1.0f)
				{
					if (GetActorLocation().X < -2000)
					{
						MovementMode = 1;
						SwitchMode = 0.0f;
						UE_LOG(LogTemp, Error, TEXT("Detected wall"));

					}

					else
					{
						MovementMode = Mode2[rand() % 2];
						UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);

						SwitchMode = 0.0f;
					}
				}
				break;

		case 3:
			MoveLeft();

			if (SwitchMode > 1.0f)
			{
				if (GetActorLocation().Y < -2000)
				{
					MovementMode = 4;
					SwitchMode = 0.0f;
					UE_LOG(LogTemp, Error, TEXT("Detected wall"));

				}
				else
				{

					MovementMode = Mode3[rand() % 2];
					UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);

					SwitchMode = 0.0f;
				}
			}
			break;

		case 4:
			MoveRight();

			if (SwitchMode > 1.0f)
			{
				if (GetActorLocation().Y > 2000)
				{
					MovementMode = 3;
					SwitchMode = 0.0f;
					UE_LOG(LogTemp, Error, TEXT("Detected wall"));

				}
				else
				{
					MovementMode = Mode4[rand() % 2];
					UE_LOG(LogTemp, Warning, TEXT("MoveMode is: %i"), MovementMode);

					SwitchMode = 0.0f;
				}

			}
			break;

		default:

			UE_LOG(LogTemp, Error, TEXT("No movement selected"));

			break;
			}

		}
	}
	//If the enemy is hit by MeleeAttack, act accordingly.
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
	// Called to bind functionality to input
	void APacmanEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

	}

	void APacmanEnemy::MoveUp()
	{
		FVector MoveUp = FVector(1.0f, 0.0f, 0.0f);

		AddMovementInput(MoveUp, MovementValue);
	}

	void APacmanEnemy::MoveDown()
	{
		FVector MoveDown = FVector(-1.0f, 0.0f, 0.0f);

		AddMovementInput(MoveDown, MovementValue);
	}

	void APacmanEnemy::MoveLeft()
	{
		FVector MoveLeft = FVector(0.0f, -1.0f, 0.0f);

		AddMovementInput(MoveLeft, MovementValue);

	}

	void APacmanEnemy::MoveRight()
	{
		FVector MoveRight = FVector(0.0f, 1.0f, 0.0f);

		AddMovementInput(MoveRight, MovementValue);

	}

	void APacmanEnemy::RotateToPlayer()
	{
		FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

		FVector NewDirection = PlayerLocation - GetActorLocation();

		SetActorRotation(NewDirection.Rotation());

	}

	void APacmanEnemy::SpawnStaticProjectile(float DeltaTime)
	{
		UWorld * World;

		World = GetWorld();

		SpawnTimer += DeltaTime;

		if (SpawnTimer > 0.3f)
		{
			World->SpawnActor<AStaticProjectile>(StaticProjectile_BP, GetActorLocation(), FRotator::ZeroRotator);
			SpawnTimer = 0.0f;
		}

	}

	void APacmanEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult)
	{
		//	if (OtherActor->IsA(AStandardEnemyProjectile::StaticClass()))
		//	{

		//	}
		if (OtherActor->IsA(APlayerMeleeAttack::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("PacmanEnemy was hit by PlayerMeleeAttack"));
			bHitByMelee = true;
			HitByMeleeTimer = 0.0f;

		}
	}
