// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "PlayerCharacter.h"
#include "StandardEnemyProjectile.h"
#include "PlayerProjectile.h"
#include "PlayerMeleeAttack.h"
#include "CurvingBossBullet.h"
#include "StaticProjectile.h"
#include "P_Up_Bulletrain.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<UCapsuleComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player character no collision box"));

	}

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	MyController->bShowMouseCursor = true;

	GetCharacterMovement()->MaxWalkSpeed = Speed;

	//OnPlayerHit.Broadcast();
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SetPlayerRotation();

	if (bMeleeDash)
	{
		MeleeDashTimer += DeltaTime;
		GetCharacterMovement()->MaxWalkSpeed = 15000.0f;
		if (MeleeDashTimer > 0.3f)
		{
			bMeleeDash = false;
			MeleeDashTimer = 0.0f;
			GetCharacterMovement()->MaxWalkSpeed = Speed;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Player Health is %i"), Health);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

		InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);
		InputComponent->BindAction("Melee", IE_Pressed, this, &APlayerCharacter::Melee);

		InputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
		InputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
}

void APlayerCharacter::Shoot()
{
	if (!bIsDead)
	{
		UWorld * World;

		World = GetWorld();

		FVector Location = GetActorLocation() + GetActorForwardVector();
		Location.Z = 10.0f;

		if (World)
		{
			World->SpawnActor<APlayerProjectile>(PlayerProjectile_BP, Location, GetActorRotation());
		}
		UGameplayStatics::PlaySound2D(World, OnSpawnProjectileSound,0.1f,1.0f,0.0f);
	}

}

void APlayerCharacter::Melee()
{
	if (!bIsDead)
	{
		UWorld * World;

		World = GetWorld();

		if (World)
		{
			bMeleeDash = true;
			World->SpawnActor<APlayerMeleeAttack>(PlayerMeleeAttack_BP, GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}

void APlayerCharacter::MoveX(float Value)
{
	if (!bIsDead)
	{
		FVector MoveX = FVector(1.0f, 0.0f, 0.0f);
		AddMovementInput(MoveX, Value);
	}
}

void APlayerCharacter::MoveY(float Value)
{
	if (!bIsDead)
	{
		FVector MoveY = FVector(0.0f, 1.0f, 0.0f);
		AddMovementInput(MoveY, Value);
	}
}

void APlayerCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	

	//TODO Putte inn invulnerabilityframes
	//SetVisibility = true/false;

	if (OtherActor->IsA(AStandardEnemyProjectile::StaticClass()))
	{
		Health--;
		StartCameraShake();
		UGameplayStatics::PlaySound2D(GetWorld(), OnPlayerHitSound, 0.1f, 1.0f, 0.0f);
		OtherActor->Destroy();
	}

	else if (OtherActor->IsA(ACurvingBossBullet::StaticClass()))
	{
		Health--;
		StartCameraShake();
		UGameplayStatics::PlaySound2D(GetWorld(), OnPlayerHitSound, 0.1f, 1.0f, 0.0f);
		OtherActor->Destroy();
	}

	else if (OtherActor->IsA(AStaticProjectile::StaticClass()))
	{
		Health--;
		StartCameraShake();
		UGameplayStatics::PlaySound2D(GetWorld(), OnPlayerHitSound, 0.1f, 1.0f, 0.0f);
		OtherActor->Destroy();
	}

	else if (OtherActor->IsA(AP_Up_BulletRain::StaticClass()))
	{
		SpawnBulletRain();
		UGameplayStatics::PlaySound2D(GetWorld(), OnP_UpSound, 0.1f, 1.0f, 0.0f);
		OtherActor->Destroy();
	}

	if (Health < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has died."));
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
		bIsDead = true;
	}
}

void APlayerCharacter::SetPlayerRotation()
{
	if (!bIsDead)
	{
		FHitResult Hit;
		bool HitResult = false;
		HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

		if (HitResult)
		{
			FVector CursorLocation = Hit.Location;

			//      UE_LOG(LogTemp, Warning, TEXT("Cursor location %s!"), *CursorLocation.ToString());

			FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);

			FVector NewDirection = TempLocation - GetActorLocation();
			NewDirection.Z = 0.0f;
			NewDirection.Normalize();
			SetActorRotation(NewDirection.Rotation());
		}
	}
}

void APlayerCharacter::StartCameraShake_Implementation()
{

}

void APlayerCharacter::SpawnBulletRain()
{
	UE_LOG(LogTemp, Warning, TEXT("Bullet Rain"));
	UWorld * World;

	World = GetWorld();

	for (int y = -Width; y < Width; y += 100)
	{
		for(int x = Heigth; x > 1350; x -= 100)
		{
			World->SpawnActor<APlayerProjectile>(PlayerProjectile_BP, FVector(x, y, 10.0f), FVector(-1.0f, 0.0f, 0.0f).Rotation());
		}
	}


}