// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "PlayerCharacter.h"
#include "StandardEnemyProjectile.h"
#include "PlayerProjectile.h"
#include "PlayerMeleeAttack.h"
#include "CurvingBossBullet.h"
#include "StaticProjectile.h"


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



}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetPlayerRotation();

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
	UWorld * World;

	World = GetWorld();

	FVector Location = GetActorLocation() + GetActorForwardVector() * SpawnBuffer;

	if (World)
	{
		World->SpawnActor<APlayerProjectile>(PlayerProjectile_BP, Location, GetActorRotation());
	}


}

void APlayerCharacter::Melee()
{
	UWorld * World;

	World = GetWorld();

	if (World)
	{
		World->SpawnActor<APlayerMeleeAttack>(PlayerMeleeAttack_BP, GetActorLocation(), FRotator::ZeroRotator);
	}
}

void APlayerCharacter::MoveX(float Value)
{
	FVector MoveX = FVector(1.0f, 0.0f, 0.0f);
	AddMovementInput(MoveX, Value);
}

void APlayerCharacter::MoveY(float Value)
{
	FVector MoveY = FVector(0.0f, 1.0f, 0.0f);
	AddMovementInput(MoveY, Value);
}

void APlayerCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AStandardEnemyProjectile::StaticClass()))
	{
		Health--;
		if (Health < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player is DEAD! Exit game please."));
		}
		OtherActor->Destroy();
	}

	else if (OtherActor->IsA(ACurvingBossBullet::StaticClass()))
	{
		Health--;
		if (Health < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player is DEAD! Exit game please."));
		}
		OtherActor->Destroy();
	}

	else if (OtherActor->IsA(AStaticProjectile::StaticClass()))
	{
		Health--;
		if (Health < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player is DEAD! Exit game please."));
		}
		OtherActor->Destroy();
	}
}

void APlayerCharacter::SetPlayerRotation()
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