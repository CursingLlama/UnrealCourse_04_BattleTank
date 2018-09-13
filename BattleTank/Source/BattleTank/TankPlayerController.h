// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, category = "Setup") void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	//Move the tank's barrel to aim point on screen
	void AimTowardsCrosshair();
	//Line traces from camera to crosshair returning true if something is hit and adjusting the out parameter
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	//Converts screen position to world vector
	bool GetLookDirection(FVector2D ScreenPosition, FVector & LookDirection) const;
	//Raycasts through look direction and returns a hit
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;

	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly) float CrossHairXLocation = 1/2.f;
	UPROPERTY(EditDefaultsOnly) float CrossHairYLocation = 1/3.f;
	UPROPERTY(EditAnywhere) float LineTraceRange = 10000000.f;
};
