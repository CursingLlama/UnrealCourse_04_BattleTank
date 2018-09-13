// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds barrel properties and methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = Input) void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Input) void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//Handles the spawning of projectiles for the tank
	void Fire();
	
protected:
	UPROPERTY(BlueprintReadOnly, category = "State") EFiringState FiringState = EFiringState::Aiming;
			
private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing") TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float LaunchSpeed = 4000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float ReloadTimeInSeconds = 3;
	float LastFiredTime = -1000;
};
