// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float Speed);

protected:
	UPROPERTY(VisibleAnywhere, category = "Components") UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components") UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components") UParticleSystemComponent* ImpactBlast = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	UFUNCTION() void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);
	virtual void Tick(float DeltaTime) override;

private:	
	
};
