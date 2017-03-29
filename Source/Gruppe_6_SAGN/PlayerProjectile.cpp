// Fill out your copyright notice in the Description page of Project Settings.

#include "Gruppe_6_SAGN.h"
#include "PlayerProjectile.h"


// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = this->FindComponentByClass<USphereComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerProjectile no collision box"));

	}
	
}

// Called every frame
void APlayerProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SetProjectileLocation(DeltaTime);

	TimeToDestroy += DeltaTime;

	if (TimeToDestroy > 15.0f)
	{
		Destroy();
	}

}

void APlayerProjectile::SetProjectileLocation(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * DeltaTime * Speed;

	SetActorLocation(NewLocation);
}

void APlayerProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit A Wall"));
	if (OtherActor->IsRootComponentStatic())
	{
		Destroy();
	}
}