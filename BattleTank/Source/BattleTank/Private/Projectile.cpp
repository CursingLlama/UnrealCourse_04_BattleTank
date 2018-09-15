// Copyright Gregory Scott Hanna 2018

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	if (ensure(CollisionMesh))
	{
		SetRootComponent(CollisionMesh);
		CollisionMesh->SetNotifyRigidBodyCollision(true);
		CollisionMesh->SetVisibility(false);
	}	
		
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	if (ensure(LaunchBlast))
	{
		LaunchBlast->SetupAttachment(RootComponent);
	}

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	if (ensure(ImpactBlast))
	{
		ImpactBlast->SetupAttachment(RootComponent);
		ImpactBlast->bAutoActivate = false;
	}
	

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
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
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
