// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float Speed);

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UFUNCTION() void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);
	

private:
	void DestroyMe();
	
	UPROPERTY(EditDefaultsOnly, category = "Setup") float DestroyDelay = 2;
	UPROPERTY(VisibleAnywhere, category = "Components") UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, category = "Components") UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, category = "Components") UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, category = "Components") URadialForceComponent* ExplosionForce = nullptr;
	UProjectileMovementComponent* ProjectileMovement = nullptr;
};
