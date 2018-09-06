// Copyright Gregory Scott Hanna 2018

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Tank = GetControlledTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player possessing tank: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player: No tank found!"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

}
