// Copyright Gregory Scott Hanna 2018

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	UE_LOG(LogTemp, Warning, TEXT("[%s] throttled by: %f"), *GetName(), Throttle);
	FVector ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;
	UPrimitiveComponent* TrackRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TrackRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}


