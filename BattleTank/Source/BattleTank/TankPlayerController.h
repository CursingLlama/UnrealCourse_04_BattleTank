// Copyright Gregory Scott Hanna 2018

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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
	ATank* GetControlledTank() const;

	//Move the tank's barrel to aim point on screen
	void AimTowardsCrosshair();
};
