// Copyright Gregory Scott Hanna 2018

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	FVector ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;
	UPrimitiveComponent* TrackRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TrackRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}


