// Copyright Gregory Scott Hanna 2018

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	if (ensure(ProjectileMovement))
	{
		ProjectileMovement->bAutoActivate = false;
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	if (ensure(ProjectileMovement))
	{
		ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovement->Activate();
	}
}

