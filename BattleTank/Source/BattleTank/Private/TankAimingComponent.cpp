// Copyright Gregory Scott Hanna 2018

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; } ///Protect Pointer
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	float Time = GetWorld()->GetTimeSeconds();
	if (bHaveAimSolution)
	{
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret))	{ return; } ///Protect Pointers
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet))
	{
		UE_LOG(LogTemp, Error, TEXT("%s: No TankBarrel assigned!"), *GetOwner()->GetName());
		return;
	}
	Barrel = BarrelToSet;

	if (!ensure(TurretToSet))
	{
		UE_LOG(LogTemp, Error, TEXT("%s: No TankTurret assigned!"), *GetOwner()->GetName());
		return;
	}
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	bool bIsReloaded = GetWorld()->GetTimeSeconds() > LastFiredTime + ReloadTimeInSeconds;
	if (Barrel && bIsReloaded)
	{
		FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator Rotation = Barrel->GetSocketRotation(FName("Projectile"));

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiredTime = GetWorld()->GetTimeSeconds();
	}
}
