// Copyright Gregory Scott Hanna 2018

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Yaw = RelativeRotation.Yaw + YawChange;
	
	SetRelativeRotation(FRotator(0, Yaw, 0));
}


