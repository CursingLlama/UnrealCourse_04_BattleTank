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

protected:
	UPROPERTY(VisibleAnywhere, category = "Components") UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, category = "Components") UParticleSystemComponent* LaunchBlast = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjectileMovement = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);
};
