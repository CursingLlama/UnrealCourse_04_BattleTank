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
	Locked,
	OutOfAmmo
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
	UFUNCTION(BlueprintCallable, Category = "Input") void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = "Input") void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	//Handles the spawning of projectiles for the tank
	UFUNCTION(BlueprintCallable, Category = "Input") void Fire();
	UFUNCTION(BlueprintCallable, Category = "Setup") void SetProjectile(TSubclassOf<AProjectile> Projectile);
	EFiringState GetFiringState();

protected:
	UPROPERTY(BlueprintReadOnly, category = "State") EFiringState FiringState = EFiringState::Aiming;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, category = "Firing") int32 Ammo = 30;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	void MoveBarrel();
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing") TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float LaunchSpeed = 5000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float ReloadTimeInSeconds = 2;
	
	float LastFiredTime;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection = FVector(0);	
};
