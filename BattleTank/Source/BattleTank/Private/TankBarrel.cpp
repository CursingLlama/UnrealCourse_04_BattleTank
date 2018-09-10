// Copyright Gregory Scott Hanna 2018

#include "TankBarrel.h"
#include "Engine/World.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinDegreesElevation, MaxDegreesElevation);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


