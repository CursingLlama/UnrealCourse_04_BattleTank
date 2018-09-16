// Copyright Gregory Scott Hanna 2018

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
///Movement handled by input bindings directly in BP


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(GetPawn())) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (ensure(PossessedTank))
		{
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
		}
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation;
	GetSightRayHitLocation(HitLocation);
	AimingComponent->AimAt(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	///Get Curson postion in pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	//Deproject crosshair
	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenPosition, FVector& LookDirection) const
{
	FVector WorldPosition;
	return DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(TNumericLimits<float>::Max());
	return false;
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player tank is dead!"));
}
