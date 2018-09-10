// Copyright Gregory Scott Hanna 2018

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	float Time = GetWorld()->GetTimeSeconds();
	if (bHaveAimSolution)
	{
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
		UE_LOG(LogTemp, Warning, TEXT("[%f] Aim solution found."), Time);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%f] No aim solution found."), Time);
	}
		
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
